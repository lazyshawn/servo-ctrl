#include <motion_axis.h>

void main()
{
	// ��ʼ��sdk��
	rm_init();

	// ��modbus rtu��
	rm_axis_handle handle = rm_open_axis_modbus_rtu("/dev/ttyS110", 115200, 0);

	// ���ô���
	rm_reset_error(handle);

	// �ϵ����Ҫ��ԭ��һ��
	rm_go_home(handle);

	// �ȴ���ԭ��
	while (rm_is_moving(handle));

	// �����˶�2��
	for (int i = 0; i < 2; i++)
	{
		// �����˶�
		rm_move_absolute(handle, 0, 10, 3000, 3000, 0.1);

		// �ȴ������˶���λ
		while (!rm_is_position_reached(handle));

		// �����˶�
		rm_move_absolute(handle, 10, 10, 3000, 3000, 0.1);

		// �ȴ������˶���λ
		while (!rm_is_position_reached(handle));
	}

	// ��ѹ�˶�
	rm_push(handle, 50, 10, 10);

	// �ȴ���ѹ��λ
	while (!rm_is_position_reached(handle));

	// �ж��Ƿ�г�/��ѹ������
	bool is_holding = rm_is_moving(handle);

	// �����˶�
	rm_move_absolute(handle, 0, 10, 3000, 3000, 0.1);
	rm_push(handle, 50, 10, 10);

	// �Ͽ���
	rm_close_axis(handle);
}

