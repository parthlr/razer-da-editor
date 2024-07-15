#include <libusb.h>
#include <stdint.h>

// Report Responses
#define RAZER_CMD_BUSY          0x01
#define RAZER_CMD_SUCCESSFUL    0x02
#define RAZER_CMD_FAILURE       0x03
#define RAZER_CMD_TIMEOUT       0x04
#define RAZER_CMD_NOT_SUPPORTED 0x05

#define LOGO_LED          0x04

struct razer_report {
	uint8_t status;
	uint8_t transaction_id;
	uint16_t remaining_packets;
	uint8_t protocol_type;
	uint8_t data_size;
	uint8_t command_class;
	uint8_t command_id;
	uint8_t args[80];
	uint8_t crc;
	uint8_t reserved;
};

void* memdup(const void* mem, size_t size);
int razer_send_control_msg(libusb_device_handle* dev, void const* data, unsigned int report_index);
int razer_get_usb_response(libusb_device_handle* dev, unsigned int report_index, struct razer_report* request_report, unsigned int response_index, struct razer_report* response_report);
int razer_get_report(libusb_device_handle* dev, struct razer_report* request, struct razer_report* response);
unsigned char razer_calculate_crc(struct razer_report* report);
int razer_send_payload(libusb_device_handle* dev, struct razer_report* request, struct razer_report* response);
razer_report get_razer_report(unsigned char command_class, unsigned char command_id, unsigned char data_size);
ssize_t razer_set_brightness(libusb_device_handle* dev, const char* buf, size_t count);