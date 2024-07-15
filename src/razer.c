#include "razer.h"
#include <stdio.h>

void* memdup(const void* mem, size_t size) {
	void* out = malloc(size);

	if (out != NULL)
		memcpy(out, mem, size);

	return out;
}

int razer_send_control_msg(libusb_device_handle* dev, void const* data, unsigned int report_index) {
	unsigned int request = 0x09;
	unsigned int request_type = 0x21;
	unsigned int  value = 0x300;
	unsigned int size = 0x5A;
	unsigned char* buf;
	int len;

	buf = (unsigned char*) memdup(data, size);
	if (buf == NULL) {
		return -ENOMEM;
	}

	len = libusb_control_transfer(dev, request_type, request, value, report_index, buf, size, 1000);

	// Wait
	Sleep(10);

	free(buf);
	if (len != size) {
		printf("Len: %i\n", len);
		printf("Size: %i\n", size);
		printf("Razer driver: device data transfer failed\n");
	}

	return ((len < 0) ? len : ((len != size) ? -EIO : 0));
}

int razer_get_usb_response(libusb_device_handle* dev, unsigned int report_index, struct razer_report* request_report, unsigned int response_index, struct razer_report* response_report) {
	unsigned int request = 0x01;
	unsigned int request_type = 0xA1;
	unsigned int value = 0x300;
	unsigned int size = 0x5A;
	int len;
	int retval;
	int result = 0;
	unsigned char* buf;

	if (request_report->transaction_id == 0x00) {
		request_report->transaction_id = 0xFF;
	}

	buf = (unsigned char*)malloc(sizeof(struct razer_report));
	if (buf == NULL) {
		return -ENOMEM;
	}

	// Send control request
	retval = razer_send_control_msg(dev, request_report, report_index);

	// Get response
	len = libusb_control_transfer(dev, request_type, request, value, report_index, buf, size, 1000);

	if (len != 90) {
		printf("Razer driver: Invalid USB response. USB Report length: %d\n", len);
		return 1;
	}

	memcpy(response_report, buf, sizeof(struct razer_report));
	free(buf);

	size_t arg_length = sizeof(response_report->args) / sizeof(uint8_t);
	if (response_report->data_size > arg_length) {
		printf("Field data_size %d in response is bigger than arguments\n", response_report->data_size);
		response_report->data_size = arg_length;
		return -EINVAL;
	}

	return result;
}

int razer_get_report(libusb_device_handle* dev, struct razer_report* request, struct razer_report* response) {
	uint16_t index = 0;
	return razer_get_usb_response(dev, index, request, index, response);
}

unsigned char razer_calculate_crc(struct razer_report* report) {
	/*second to last byte of report is a simple checksum*/
	/*just xor all bytes up with overflow and you are done*/
	unsigned char crc = 0;
	unsigned char* _report = (unsigned char*)report;

	unsigned int i;
	for (i = 2; i < 88; i++) {
		crc ^= _report[i];
	}

	return crc;
}

int razer_send_payload(libusb_device_handle* dev, struct razer_report* request, struct razer_report* response) {
	int err;

	request->crc = razer_calculate_crc(request);

	err = razer_get_report(dev, request, response);

	if (response->remaining_packets != request->remaining_packets ||
		response->command_class != request->command_class ||
		response->command_id != request->command_id) {
		printf("Response doesn't match request\n");
		return -EIO;
	}

	switch (response->status) {
	case RAZER_CMD_BUSY:
		// TODO: Check if this should be an error.
		printf("Device is busy\n");
		break;
	case RAZER_CMD_FAILURE:
		printf("Command failed\n");
		return -EIO;
	case RAZER_CMD_NOT_SUPPORTED:
		printf("Command not supported\n");
		return -EIO;
	case RAZER_CMD_TIMEOUT:
		printf("Command timed out\n");
		return -EIO;
	}

	return 0;
}

struct razer_report get_razer_report(unsigned char command_class, unsigned char command_id, unsigned char data_size) {
	struct razer_report new_report = { 0 };
	memset(&new_report, 0, sizeof(struct razer_report));

	new_report.status = 0x00;
	new_report.transaction_id = 0x00;
	new_report.remaining_packets = 0x00;
	new_report.protocol_type = 0x00;
	new_report.command_class = command_class;
	new_report.command_id = command_id;
	new_report.data_size = data_size;

	return new_report;
}

ssize_t razer_set_brightness(libusb_device_handle* dev, uint8_t brightness, size_t count) {
	//unsigned char brightness = (unsigned char)strtoull(buf, NULL, 10);

	struct razer_report request = get_razer_report(0x0F, 0x04, 0x03);
	request.args[0] = 0x01;
	request.args[1] = 0x04; // logo led ID
	request.args[2] = brightness; // brightness
	request.args[3] = 0xA9; // extra args
	request.args[3] = 0xA9; // extra args
	request.args[3] = 0xA9; // extra args
	request.args[3] = 0xA9; // extra args
	request.args[3] = 0xA9; // extra args
	request.transaction_id = 0xFF;

	struct razer_report response = { 0 };

	razer_send_payload(dev, &request, &response);

	return count;
}