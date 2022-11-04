#pragma once

#define WIN32_LEAN_AND_MEAN

#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

namespace dreamtea
{
	extern const char* DREAMTEA_IP;
	extern const char* DTA_PORT;

	class EventHandler
	{
	public:
		virtual void on_right_click();
	};

	void connect(const char* ip, const char* port);

	void register_artifact(EventHandler* handler);

	void send_data(const char* data);

	void loop();
}
