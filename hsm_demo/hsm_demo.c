// hsm_demo.cpp : Defines the entry point for the application.
//

#include "time_bomb_user.h"
#include "time_bomb_user_types.h"

static tb_user_data_t user_data;

int main()
{
	hsm_init(&time_bomb_instance, &user_data);

	hsm_push_event(&time_bomb_instance, HSM_EVENT_ID_RESET);

	hsm_push_event(&time_bomb_instance, HSM_EVENT_ID_TIME_BOMB_ARM_BUTTON_PRESS);

	for (uint8_t i = 0; i < 5; i++)
	{
		hsm_push_event(&time_bomb_instance, HSM_EVENT_ID_TIME_BOMB_ON_TIMER);
	}

	hsm_push_event(&time_bomb_instance, HSM_EVENT_ID_TIME_BOMB_PHONE_CALL_RECEIVED);

	for (uint8_t i = 0; i < 20; i++)
	{
		hsm_push_event(&time_bomb_instance, HSM_EVENT_ID_TIME_BOMB_ON_TIMER);
	}

	return 0;
}
