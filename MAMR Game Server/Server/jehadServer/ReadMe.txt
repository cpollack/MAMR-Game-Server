// ���˵��
// �ɽ��ޣ�2002.10.23
///////////////////////////////////////////////////////////////////////

���Ĵ������ں��Ĺ��̵ġ�TODO��������ӡ�

����ģ�飺
	MsgServer
		SocketKernel
		WorldKernel
		MapGroupKernel
		GameBaseCode(�ù��̴�����������������)
		Comm
		Common(���߿⣬���������й���)
		MapData


�߳�ģ�飺
	shell
	socket
	world
	*map_group


��¼���̣�
����ҵ�¼ʱ����WORLD_KERNEL����������Ϣ����
��MSG_LOGINʱ�������ת��MAPGROUP_KERNEL��
���˳�ʱ�����෴��


ͬ������
����Ҵ�һ������ת����һ������ʱ���ͻ���Ҫ�ȴ���������Ӧ��������ϴ���Ϣ��������������ܻᶪʧ����Ϣ��


NPC��Ϣ�㲥��
��TARGET_NPC_IDָ��ΪBROADCAST_NPC_ID(��ֱ��ΪID_NONE)����ʱֻ��Ҫ��NPC����������һ����Ϣ����NPC�������Լ�
����ת�����ļ���NPC��


��ҽ��벽�裺
���������ӣ������������ġ�
����¼������ģ�ת����ͼ�顣
����¼��ͼ�顣


���ת��ͼ�飺
����ҵǳ���ͼ�顣
��֪ͨ�������������л���
������һ��ͼ�鷢��������ݡ�
��֪ͨ��һ��ͼ������ҵ�¼��


����˳����裺
���Ӻ��Ŀ�ʼ�˳���
	��WORLD����MAPGROUP����CloseSocket�ӿڣ����LOGOUT��ͬʱ����SOCKET���� SOCKET_BREAKCONNECT��SOCKET���ĶϿ�SOCKET(���߰�1-1����Ϣ)��ִ�С���������˳�����
��������㿪ʼ�˳���
	��SOCKET���ĵ���Ϊ��
		1-1�����͸����һ��MAPGROUP����KERNEL_CLOSEKERNEL��Ϣ��
		1-6�����յ�MAPGROUP��SETPROCESSID��Ϣʱ���ظ�KERNEL_CLOSEKERNEL��
		1-7�����յ�SOCKET_CLOSEKERNELʱ������˳�����!
	��WORLD���ĵ���Ϊ��
		2-1��KERNEL_CLOSEKERNEL������˳�WORLD��ת����SOCKET����SOCKET_CLOSESOCKET��
	��MAPGROUP���ĵ���Ϊ��
		3-1��KERNEL_CLOSEKERNEL��������ڱ�MAPGROUP��ת����ǰһ���߳�(MAPGROUP��WORLD) KERNEL_CLOSEKERNEL��Ϣ��
		3-2��KERNEL_CLOSEKERNEL����Ҵ�MAPGROUP�����˳�ʱ��ֱ��֪ͨWORLD����KERNEL_CLOSEKERNEL��Ϣ��
		3-6�����������ڴ�WORLD��MAPGROUP�����ߴ�MAPGROUP��MAPGROUP������ҵ���MAPGROUPʱ�������SETPROCESSID����ʱSOCKET��ظ�KERNEL_CLOSEKERNEL(���ٴη�����Ϣ)����ʱ��Ҳ�������˳���


���ɣ�
��CSynData�����ݲ㣬���г�Ա����ʹ��private����ֹCSyndicate���ȡ�������ⲿ�ӿڱ�����ԭ�ӵġ�
	��QuerySynchro()���ڲ��ӿڡ��޸��Լ���״̬��

��CSyndicate����CSynData������ֻ�ṩֻ���ӿڡ�
	��QueryChange()���ṩ�޸ĵĽӿڡ�

��CSynShell���ṩ����ͼ�����Ĵ������
	��QueryChange()�����޸���Ϣת����������
	��QuerySynchro()�����û���ӿڡ�

��CSynWorldShell���ṩ����ͼ�����Ĵ������
	��QueryChange()�����û���ӿڡ�
	��QuerySynchro()���ڲ��ӿڡ��޸��Լ���״̬��ͬʱ�㲥������MapGroup��

��CSynManager��
	�������°��ɣ���WORLD���룬��ɺ�������MAPGROUP�㲥���������MAPGROUP�������ݿ��¼��
	����ɢ���ɣ���WORLD���룬��ɺ�������MAPGROUP�㲥��������ɾ�����ݿ��¼��

��CSynWorldManager��
	���½����ɡ�
	��ɾ�����ɡ�


��¼��Ϣ���̣�
	���ͻ����ȵ�¼���ʺŷ��������ϴ�CMsgAccount��¼�ʺŷ��������ʺŷ������᷵�ظ��ͻ���XXX��Ϣ��
	���ʺŷ�����������Ϸ�������´�CMsgConnect_A
	��ͬʱ�ͻ��˻�����SOCKET�����ϴ�CMsgConnect
	����������յ�CMsgConnect_A��CMsgConnect����ͻ��˷���CTalk��_TXTATR_ENTRANCEƵ����Ϣ��ͬʱ���ͼ�鷢MAPGROUP_LOGIN�ڲ���Ϣ������ҵ�¼��ͼ�顣
	��

