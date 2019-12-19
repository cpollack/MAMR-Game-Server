// action list
// paled, 2003.1.25

////////////////////////////////////////////////////////////////////////
// "%%" ��ʾ����ʾ�� "%" ����
// "%nnXXX" ��ʾ��ʾ��ȣ�һ������롣�����ᰴʵ�ʳ�����ʾ��(��idΪ1234��NPC��"%6id"��ʾΪ"1234  ")

// ϵͳ���� //////////////////
const char PARAM_DATE_STAMP[]			= "date_stamp";					// �����ڼ���
const char PARAM_TIME[]					= "time";						// �����ڼ���
const char ACCEPT_STR_[]				= "accept";						// �ͻ����ϴ���һ���Ӵ� // %accept0 ~ %accept3

// ITEM���� //////////////////
const char	PARA_ITEM_TYPE[]			= "item_type";
const char	PARA_ITEM_DATA[]			= "item_data";

// NPC���� //////////////////
const char	PARA_DATASTR[]				= "datastr";
const char	PARA_DATA_[]				= "data";							// %data0 ~ %data3
const char	PARA_NAME[]					= "name";							// npc name
const char	PARA_NPC_ID[]				= "id";								// npc id in database
const char	PARA_NPC_X[]				= "npc_x";
const char	PARA_NPC_Y[]				= "npc_y";
const char	PARA_NPC_OWNERID[]			= "npc_ownerid";

// USER���� ////////////////
const char	PARA_USER_ID[]				= "user_id";
const char	PARA_USER_MAPID[]			= "user_map_id";
const char	PARA_USER_MAPX[]			= "user_map_x";
const char	PARA_USER_MAPY[]			= "user_map_y";
const char	PARA_USER_HOME[]			= "user_home_id";
const char	PARA_SYN_ID[]				= "syn_id";
const char	PARA_SYN_NAME[]				= "syn_name";
const char	PARA_USER_NAME[]			= "user_name";
const char	PARA_MATE_NAME[]			= "mate_name";
const char	PARA_MAP_OWNER_ID[]			= "map_owner_id";
const char	PARA_MAP_OWNER_TYPE[]		= "map_owner_type";
const char	PARA_ALLY_SYN_[]			= "ally_syn";						// %ally_syn0 ~ %ally_syn4
const char	PARA_ENEMY_SYN_[]			= "enemy_syn";						// %enemy_syn0 ~ %enemy_syn4
const char	PARA_TUTOREXP_[]			= "tutor_exp";						// ��ʦ����
const char	PARA_STUDENT_EXP_[]			= "student_exp";					// ͽ�ܹ��׵ľ���
const char	PARA_EXPLOIT_[]				= "exploit";						// ��ѫֵ
//���ɲ���
const char	PARA_AVAILABLE_FUND[]		= "available_fund";					// ��ȡ���ɵĿ��Է������
// user �� iter ���� ////////////////
const char	PARA_ITER_VALUE[]			= "iter_value";
const char	PARA_ITER_SYN_NAME[]		= "iter_syn_name";
const char	PARA_ITER_SYN_LEADER[]		= "iter_syn_leader";
const char	PARA_ITER_SYN_MONEY[]		= "iter_syn_money";
const char	PARA_ITER_SYN_AMOUNT[]		= "iter_syn_amount";
const char	PARA_ITER_SYN_FEALTY[]		= "iter_syn_fealty";
const char	PARA_ITER_MEMBER_NAME[]		= "iter_member_name";				// %iterΪ���ID�������������
const char	PARA_ITER_MEMBER_RANK[]		= "iter_member_rank";				// %iterΪ���ID��������ҵȼ��ƺ�
const char	PARA_ITER_MEMBER_PROFFER[]	= "iter_member_proffer";
const char	PARA_ITER_WANTED[]			= "iter_wanted";
const char	PARA_ITER_POLICEWANTED[]	= "iter_police_wanted";
const char	PARA_ITER_GEMSUPQUALITY[]	= "iter_upquality_gem";
const char	PARA_ITER_GEMSUPLEVEL[]		= "iter_uplevel_gem";
const char	PARA_ITER_COST_DURRECOVER[]	= "iter_cost_durrecover";			// 
const char	PARA_ITER_GAME_CARD[]		= "iter_game_card";					// 
const char	PARA_ITER_GAME_CARD2[]		= "iter_game_card2";				// 

const char	PARA_ITER_TABLE_DATASTR[]	= "iter_table_datastr";
const char	PARA_ITER_TABLE_DATA_[]		= "iter_table_data";				// %iter_table_data0 ~ %iter_table_data3

const char	PARA_ITER_ITEM_DATA[]		= "iter_item_data";

//---����ϵͳ��iter---begin
const char	PARA_ITER_TASK_USERNAME[]		= "iter_task_username";		//������ҵ�cq_user���е�name�ֶ�
const char	PARA_ITER_TASK_COMPLETENUM[]	= "iter_task_completenum";  //��������ɴ���ȡֵ������������ɴ���
const char	PARA_ITER_TASK_BEGINTIME[]		= "iter_task_begintime";    //������ʼʱ��ȡֵ����������ʼʱ��
//---����ϵͳ��iter---end

////////////////////////////////////////////////////////////////////////
enum {
		// system part, need user ptr --------------------------------------------------------------------------
		ACTION_SYS_FIRST			= 100,
		ACTION_MENUTEXT				= 101,			// �˵��ı���data:��ʾ����(ȱʡΪ0), param="text"(��ѡ): ��ʾ�ı��������Ϳɰ����ո�Ҳ��Ϊ���С�
		ACTION_MENULINK				= 102,			// �˵������ӡ�"text task_id align": align(��ѡ): ����ģʽ(ȱʡ/0:�����; 5:����; 9:�Ҷ���; a(1-9)b(2-8):������,��a/b�п���ʼ��ʾ,9Ϊ�Ҷ���)
		ACTION_MENUEDIT				= 103,			// �˵������"len task_id text": len:������ĳ��ȣ�text(��ѡ)����ʾ�����֣�align������ģʽ(ȱʡ�����������������������Ƕ�������ֵĵڼ��ַ���)����˵�������ж��������ɽ�����Բ��ť���֣�ÿ��ֻ�ϴ�һ����
		ACTION_MENUPIC				= 104,			// �˵�ͼƬ��"x y pic_id task_id"��task_id(��ѡ)����ʾͼƬ���ԡ�������ͼƬ����������ʾ�ı���
		ACTION_MENUBUTTON			= 110,			// �˵���ť����ʽͬ�����ӡ�
		ACTION_MENULISTPART			= 111,			// �˵��б��"task_id iter text...", ��ҵ�ѡ�б�󣬻ᴥ��task_id������iter�����ҵ�%iter�����С�
		ACTION_MENUCREATE			= 120,			// �˵�������"cancel_task_id"(��ѡ): ǿ�йرղ˵�ʱ������TASK
		ACTION_RAND					= 121,			// �������ʡ�"data1 data2"��"10 100"��ʾ��1/10�Ļ�����true��
		ACTION_RANDACTION			= 122,			// ���Action "action0 action1... action7"��8���������һ��ִ��
		ACTION_CHKTIME				= 123,			// dataΪʱ������ 0-��鵱ǰ��������ϸʱ�� "%d-%d-%d %d:%d %d-%d-%d %d:%d"; 1-�����ĳ��ʱ��"%d-%d %d:%d %d-%d %d:%d", 2-�����ĳ��ʱ��"%d %d:%d %d %d:%d", 3-�����ĳ��ʱ��"%d %d:%d %d %d:%d", 4-�����ʱ��"%d:%d %d:%d", 5-���Сʱʱ��"%d %d"(ÿ��Сʱ�ĵڼ��ֵ��׼���)
		ACTION_POSTCMD				= 124,			// ��ͻ��˷��ͽ������dataΪ������
		ACTION_BROCASTMSG			= 125,			// ȫ�������㲥������Ϣ��dataΪƵ����paraΪ����
		ACTION_MESSAGEBOX			= 126,			// �ÿͻ��˵����Ի���dataΪ�Ի�������(0-99)��param=���ִ�������
		ACTION_SYS_LIMIT			= 199,

		// npc part, need npc ptr --------------------------------------------------------------------------
		ACTION_NPC_FIRST			= 200,
		ACTION_NPC_ATTR				= 201,			// �޸Ļ�������NPC�����ԡ�"attr opt data npc_id"������3�����������ָ��npc_id����NPC�����ڱ���ͼ���С�attr��ѡ��"ownerid"(=,==)��"ownertype"(=,==)��"lookface"(=,==)��"data?"(=,+=,==,<,<=,>,>=,pass. pass�����ֶ��д��DateStamp����һ����������. data��Ϊ"accept")��"datastr"(=,==)��"life"(=)��"maxlife"(=)
//		ACTION_NPC_REQUESTSHIFT		= 202,			// ֪ͨ�ͻ���ƽ��һ��NPC��param="idNextTask"��
//		ACTION_NPC_SHIFT			= 203,			// ƽ�Ƶ�ǰNPC����ͬ��ͼ�ƶ����޶�̬NPC��
		ACTION_NPC_ERASE			= 205,			// ɾ����ǰNPC���޶�̬NPC��ע�⣺ɾ���󣬲�Ҫ�ٶԴ�NPC���в�����dwData��Ϊ0����ʾɾ������ͼ������typeΪdwData��NPC��param="idMap type": ɾ��ָ����ͼ��ĳЩNPC��
		ACTION_NPC_MODIFY			= 206,			// ���߳��޸�ָ������NPC�����ԡ�"npc_id attr opt data"��attr��ѡ��"lookface"(=)��"data?"(=)��"datastr"(=)
		ACTION_NPC_RESETSYNOWNER	= 207,			// ���ð��ɵ�ͼ�����ˡ������ڰ��ɱ�־NPC��ͳ�ư���ս����һ������OWNER_ID��ͬʱ�������ս�������й����Զ�ֹͣ��(δ��ֹ��ͼ��ս����־)
		ACTION_NPC_FIND_NEXT_TABLE	= 208,			// ������һ���б����IDд��TASK_ITERATOR�������ڴ��б��NPC��param="type", ��Ӧcq_table��type�ֶΡ�
		ACTION_NPC_ADD_TABLE		= 209,			// ���б������һ��, type��idKey��ͬ�ĻᱻԤ��ɾ��(idKeyΪ0ʱ����ɾ��)�������ڴ��б��NPC��param="type idKey data0 data1 data2 data3 szData", ����2��������
		ACTION_NPC_DEL_TABLE		= 210,			// ���б���ɾ�����з���������������ڵ�Ҳ����true�������ڴ��б��NPC��param="type idKey data0 data1 data2 data3 szData", ����2������, ����Ϊ0��ʾ��ƥ�䣬���в�Ϊ0�����б���ȫ��ͬ�Ļ�ɾ������paramʱ��ɾ����ǰ��¼(iteratorָ���ļ�¼)�����Ƿ���true��
		ACTION_NPC_DEL_INVALID		= 211,			// ���б���ɾ�����й��ڵ�������ڵ�Ҳ����true�������ڴ��б��NPC��param="type idx", idx��ʾ����(%date_stamp)������ĸ�data�С�[����idxΪ3��ʾ���ڴ����data3�У�����data3�е�����С�ڽ������ڵ����ɾ����]
		ACTION_NPC_TABLE_AMOUNT		= 212,			// ����б��������>=dataʱ����false��<dataʱ����true��param�����塣
		ACTION_NPC_SYS_AUCTION      = 213,          // LW��NPC��ʼϵͳ����,DATAΪNPC��ID,param Ϊϵͳ��ʽ��ʼ����ʾ
		ACTION_NPC_DRESS_SYNCLOTHING = 214,			//�����ɷ�װ
		ACTION_NPC_TAKEOFF_SYNCLOTHING = 215,		//�Ѱ��ɷ�װ
		ACTION_NPC_AUCTIONING        = 216,         //�ж��Ƿ�����Ʒ����������DATAΪNPC��ID��PARAM��type��0.��ʾ�鿴ϵͳ������Ʒ��1.��ʾ�鿴�����Ʒ
		ACTION_NPC_LIMIT			= 299,		

		// map part, need curr map --------------------------------------------------------------------------
		ACTION_MAP_FIRST			= 300,
		ACTION_MAP_MOVENPC			= 301,			// ��npc�ƶ���ָ���ĵ�ͼ��λ��(�����ڹ̶�NPC)��data Ϊָ����npc��ID, paramΪ "idMap nPosX nPosY"��ע�⣺���ƶ����õ�ͼ��(0,0)���꣬�Ա�����NPC��
		ACTION_MAP_MAPUSER			= 302,			// �ж�ָ����ͼ�е��û�����, data Ϊָ����ͼID, paramΪ "cmd opt data",
													//  cmd֧��"map_user"��"alive_user", opt����Ϊ"==, <=, >="��dataΪ����
		ACTION_MAP_BROCASTMSG		= 303,			// �㲥��Ϣ, data Ϊ��ͼid, szParamΪ�㲥����Ϣ
		ACTION_MAP_DROPITEM			= 304,			// ��ͼ����ָ����Ʒ, szParamΪ"idItemType idMap nPosX nPosY"
		ACTION_MAP_SETSTATUS		= 305,			// ���õ�ͼ״̬��֧��EVENT��param="mapid status_bit data", status_bit = { STATUS_WAR=1, }, data=0��1��
		ACTION_MAP_ATTRIB			= 306,			// ��顢�޸ĵ�ͼ�����ԡ�param="field opt data idMap", ��������3����ȱʡΪ��ǰ��ͼ��field="synid"(opt="=="��"=")��field="status"(opt="test"��"set"��"reset")��field="type"(opt="test")��field="res_lev"(opt="="��"=="��"<")��field="mapdoc"(opt="="��"==")�� portal0_x(=), portal0_y(=),field ="castle"(opt="==")
		ACTION_MAP_REGION_MONSTER	= 307,			// ���ָ����ͼ��ǰ��ͼ��ĳ�����ڹ���������param="map_id region_x region_y region_cx region_cy monster_type opt data"��map_idΪ0ʱ��ʾȡ��ǰ��ͼ��monster_typeΪ0��ʾ��������ͣ�opt֧�֡�==���͡�<����

		ACTION_MAP_CHANGEWEATHER	= 310,			// �޸��������REGION��������param="Type Intensity Dir Color KeepSecs", Type, Intensity=0~999, Dir=0~359, Color=0x00RRGGBB, KeepSecs=seconds
		ACTION_MAP_CHANGELIGHT		= 311,			// �޸���ҵ�ͼ�����ȡ�param="idmap light secs", light=0xAARRGGBB(0xFFFFFFFF��ʾ�ָ�), secsΪ0 : ��ʾ���øı�
		ACTION_MAP_MAPEFFECT		= 312,			// ��ָ����ͼ��ָ���ص���ʾ��ͼ��Ч, param = "idMap x y EffectName"
		ACTION_MAP_CREATEMAP		= 313,			// ����һ�ŵ�ͼ�����ӵ���ǰNPC��(npc����ΪLINK_NPC)����Ҫ��Ҷ���param="name owner_type owner_id mapdoc type portal_x portal_y reborn_map reborn_portal res_lev"��partalָ��ڵ����꣬res_lev��ʾ��ͼ�ȼ�(��������)��
		ACTION_MAP_FIREWORKS		= 314,			// �����

		ACTION_MAP_LIMIT			= 399,

		// item action only part, need pUser+pItem ptr --------------------------------------------------------------------------
		ACTION_ITEMONLY_FIRST		= 400,
		ACTION_ITEM_REQUESTLAYNPC	= 401,			// ֪ͨ�ͻ��˷���һ��NPC��param="idNextTask type sort lookface region", ����4��������region��ʾcq_region��type
		ACTION_ITEM_COUNTNPC		= 402,			// ���ͬ��ͼ��NPC������param="field data opt num", field="name"(������)��"type"(������)��"all"(����NPC)��"furniture"(�Ҿ�), data=Ҫͳ�Ƶ����ֻ�����(all��furniture��0), opt="<"��"=="��
		ACTION_ITEM_LAYNPC			= 403,			// ����һ��NPC�������ɹ��󣬸�NPC���ǵ�ǰ����NPC��owner_id���Զ�����Ϊ����ID�����ID��param="name type sort lookface ownertype  life region base linkid  task0 task0 ... task7  data0 data1 data2 data3 datastr"������5�����������ӵĵȼ�����data3�С�
		ACTION_ITEM_DELTHIS			= 498,			// ɾ����ǰ������Ʒ��ע�⣺����Ϊ���һ��ACTION��
		ACTION_ITEMONLY_LIMIT		= 499,

		// user item part, need user ptr --------------------------------------------------------------------------
		ACTION_ITEM_FIRST			= 500,
		ACTION_ITEM_ADD				= 501,			// �����Ʒ��data=itemtype_id, param="amount amount_limit ident gem1 gem2 magic1 magic2 magic3 data warghostexp gemtype availabletime", param��ʡ�ԣ�����ȱʡֵΪ0(��ʾ���޸�)
		ACTION_ITEM_DEL				= 502,			// ɾ����Ʒ��data=itemtype_id, param��Ϊ0ʱ���ɵ�������Ʒ��ͬʱɾ�����������dataΪ0��param��ʾҪɾ������Ʒ����
		ACTION_ITEM_CHECK			= 503,			// �����Ʒ��data=itemtype_id, param��Ϊ0ʱ��ͬʱ�����Ʒ������(���;ö�)������Ʒ����ﵽҪ�������(���;ö�)���С�����dataΪ0��param��ʾҪ�ҵ���Ʒ����
		ACTION_ITEM_HOLE			= 504,			// �����򶴡�param ֧�� "ChkHole HoleNum" ����"MakeHole HoleNum"��NumΪ1����2
		ACTION_ITEM_REPAIR			= 505,			// װ������dataΪָ��װ����λ�á�
		ACTION_ITEM_MULTIDEL		= 506,			// ɾ��������Ʒ, paramΪ "idType0 idType1 num"����ɾ��num��idType0-idType1����Ʒ��
		ACTION_ITEM_MULTICHK		= 507,			// ��������Ʒ, paramΪ "idType0 idType1 num"�������num��idType0-idType1����Ʒ��
		ACTION_ITEM_LEAVESPACE		= 508,			// ��鱳��ʣ��ռ䡣param="space weight packtype"
													// ����packtype��ȡֵ��ΧΪ50 ~ 53
													// 50����ͨ��Ʒ����
													// 51��ħ�걦ʯ����
													// 52�����޵�����
													// 53�����ޱ���

		ACTION_ITEM_UPEQUIPMENT		= 509,			// װ������, param��ʽΪ"cmd position", 
													// cmd֧��"up_lev", "up_quality", "recover_dur"
													// position Ϊװ��λ��, ��������
													/*	ITEMPOSITION_HELMET		= 1;
														ITEMPOSITION_NECKLACE	= 2;
														ITEMPOSITION_ARMOR		= 3;
														ITEMPOSITION_WEAPONR	= 4;
														ITEMPOSITION_WEAPONL	= 5;
														ITEMPOSITION_RINGR		= 6;
														ITEMPOSITION_RINGL		= 7;
														ITEMPOSITION_SHOES		= 8;
														ITEMPOSITION_MOUNT		= 9*/

		ACTION_ITEM_EQUIPTEST		= 510,			// ��ƷƷ�ʼ���, 
													// param "equip_pos cmd opt num", 
													// equip_posͬ��position����, 
													// cmd֧��"level", "quality", "durability", "max_dur"
													// opt֧��"==, >=, <=",
													// numΪ����, cmdΪ"durability"��"max_dur"ʱ, -1Ϊ���ֵ
		ACTION_ITEM_EQUIPEXIST		= 511,			// װ�����ڼ���, dataΪװ��λ��
		ACTION_ITEM_EQUIPCOLOR		= 512,			// װ����ɫ�ı�, param = "equip_pos color", equip_pos֧������
													/*	ITEMPOSITION_HELMET		= 1;
														ITEMPOSITION_ARMOR		= 3;
														ITEMPOSITION_WEAPONL	= 5; */	// ITEMPOSITION_WEAPONL �����Ƕ��Ʋ�������
		ACTION_ITEM_FIND			= 513,			// ����һ����Ʒ��type����user��iterator�С�data=itemtype_id������dataΪ0��param��ʾҪ���ҵ���Ʒ����
		ACTION_ENCASH_CHIP          = 514,          // �ó��뻻Ǯ��Ǯ���ڣɣ�����еģģ�����ֶ�
		ACTION_ITEM_LIMIT			= 599,

		// user npc only part, need not user ptr --------------------------------------------------------------------------
		ACTION_NPCONLY_FIRST		= 600,
		ACTION_NPCONLY_CREATENEW_PET= 601,			// ����һ��MONSTER��OWNERID��OWNERTYPE��NPC��ͬ��param="x y generator_id type data name", ����4������, ����name�������generator���ڿ��ƹ�����Χ��cq_generator�е�type�����塣x��y����ͼ�ľ������ꡣ
		ACTION_NPCONLY_DELETE_PET	= 602,			// ɾ������ͼ������MONSTER��OWNERID��OWNERTYPE��NPC��ͬ��param="type data name", ����1������, data��Ϊ0��ͬʱƥ��data, ����name��ͬʱƥ�����֡�
		ACTION_NPCONLY_MAGICEFFECT	= 603,			// NPC��һ��ħ��Ч����param="source_id magic_type magic_level target_id data"
		ACTION_NPCONLY_MAGICEFFECT2	= 604,			// NPC��һ����Чħ����param="source_id magic_type magic_level x y target_id data", ����5��������
		ACTION_NPCONLY_LIMIT		= 699,

		// user syndicate part --------------------------------------------------------------------------
		ACTION_SYN_FIRST			= 700,
		////////////////////////////////////////////////////////
		// ����Action����
		ACTION_SYN_CREATE			= 701,			// ������Ҫ����������֡�param="level money leave_money", ��������Ϊ��Ҫ����ҵȼ�����Ҫ���ֽ��������ɳ����������ֽ�����
		ACTION_SYN_DESTROY			= 702,			// ��ɢ��ִ��Action�����Ϊ�ų������ų����ֶӳ���ʱ�򣬷ֱ��ʾ��ɢ���ɡ����š��ֶ�
		ACTION_SYN_DONATE			= 703,			// ����Ҫһ�������
		ACTION_SYN_CREATE_SUB		= 708,			// ���Ӱ�(���ų�ִ�о��Ǵ������ţ����ų�ִ�о��Ǵ����ֶ�)��
													// ���Ҫ�����������(���Ȳ�����16BYTE)��
		ACTION_SYN_COMBINE_SUB		= 710,			// �ϲ��Ӱ��ɡ�ִ��Action��������Ӱ��ɵİ������ϲ���������
		ACTION_SYN_ATTR				= 717,			// �����޸İ������ԣ�������С��3����ȱʡ����ID�ǵ�ǰ��ҵİ���ID��
													// param="szField szOpt data syn_id", szField��ѡ��
													// ����"money"	(opt��ѡ"+=", "<"), 
													// ������"repute"	(opt��ѡ"+=", "<"),
													// ������"membernum"(optΪ"<"),
													// �����ɣ�"fealty"	(optΪ"=="),
													// �ȼ���"level"	(opt��ѡ"=", "+=", "<", "==")
		ACTION_SYN_ALLOCATE_SYNFUND	= 729,			// ������ɻ�����Ҫ������ݾ�����(��಻�����ܻ����50%)
		ACTION_SYN_RENAME			= 731,			// ���������ɡ��������Ӱ��ɣ����Ӱ��ɵİ���ִ��
		////////////////////////////////////////////////////////

		ACTION_SYN_DEMISE			= 704,			// ����, ֻ������ų����ã����ų��ͷֶӳ���������
													// ���Ҫ����������֡�param= "level"����ʾ�������õ������Ҫ�ĵȼ�
		ACTION_SYN_SET_ASSISTANT	= 705,			// ����Ϊ������, ���Ҫ����������֡�
		ACTION_SYN_CLEAR_RANK		= 706,			// ���ְ��, ���Ҫ����������֡�
		ACTION_SYN_PRESENT_MONEY	= 707,			// ��Ǯ���������ɡ�����Ҫ�����Ǯ�������������ɵ�IDΪTASK_ITERATOR(�μ�ACTION_SYN_FIND_BY_NAME)����Ǯ��������10000
		ACTION_SYN_CHANGE_LEADER	= 709,			// �����Ӱ��ɵİ������������Ӱ����°�����ӣ������Ӱ������֡�param= level��Ҫ����°����ȼ�
		ACTION_SYN_ANTAGONIZE		= 711,			// ����, ���Ҫ����������֡�
		ACTION_SYN_CLEAR_ANTAGONIZE	= 712,			// ������У����Ҫ����������֡�
		ACTION_SYN_ALLY				= 713,			// ���ˣ�Ҫ�������������
		ACTION_SYN_CLEAR_ALLY		= 714,			// �������,���Ҫ����������֡�
		ACTION_SYN_KICKOUT_MEMBER	= 715,			// �����ֿ������ڣ����Ҫ����������֡�
		ACTION_SYN_CREATENEW_PET	= 716,			// (����)����һ�������ػ��ޡ�param="generator_id type data", ������������, ����accept�������generator���ڿ��ƹ�����Χ��cq_generator�е�type�����塣
		ACTION_SYN_CHANGESYN		= 718,			// ����ת�ÿڡ��ÿ�ת�ÿڣ��ÿں��ܰﻥת����Ҫ���ں�����(�����)��ӣ�һ��תһ�ˡ���Ҫ����Ҫת����ÿ�����(���������)��ת��ȥ֮ǰְλ�ᱻ�Զ�ȡ����
		ACTION_SYN_CHANGE_SUBNAME	= 719,			// �޸��ÿ�����ֻ�������ֳ���6���ֽڵ��ÿڡ����򷵻�FALSE��(��ʱ����)

		ACTION_SYN_FIND_NEXT_SYN	= 720,			// ������һ�����ɣ���IDд��TASK_ITERATOR
		ACTION_SYN_FIND_BY_NAME		= 721,			// �����ֲ��Ұ��ɣ����Ҫ����������֡���IDд��TASK_ITERATOR
		ACTION_SYN_FIND_NEXT_SYNMEMBER	= 722,		// ������һ�����ڣ���IDд��TASK_ITERATOR
		ACTION_SYN_SAINT            = 724,          // ʥ��ʿ�ŵ������Ĳ��� "=, >="
		ACTION_SYN_RANK				= 726,			// �޸�RANK��ACCEPT="rank name"��ֻ�޸�RANK=50�����¡�param="RANK50�ĵȼ����� RANK40�� 30�� 20 10"��paramΪ�������ơ�
				
		ACTION_SYN_UPMEMBERLEVEL		=728,
		ACTION_SYN_APPLLY_ATTACKSYN		=730,		//���빥�����
		
		ACTION_SYN_LIMIT			= 799,

		// monster part --------------------------------------------------------------------------
		ACTION_MST_FIRST			= 800,
		ACTION_MST_DROPITEM			= 801,			// monster��ɱ�������Ʒ����Ǯ, param "dropitem itemtype"����"dropmoney money"
													//monster��ɱ���������, param "droptrap traptype lifeperiod"��
		ACTION_MST_MAGIC			= 802,			// ��鷨����
													// param "check type"(ѧ��type���͵ķ���), 
													// "check type level"(ѧ��type���͵ķ������ҵȼ�Ϊlevel��), 
													// "learn type"(ѧ��type�෨�����ȼ�Ϊ0)��
													// "uplevel type"(type�෨����һ��)
		ACTION_MST_LIMIT			= 899,		

		// user attr part --------------------------------------------------------------------------
		ACTION_USER_FIRST			= 1000,
		ACTION_USER_ATTR			= 1001,			// ������Ե��޸ĺͼ�顣"attr opt data"��attr��ѡ��
													//		"life"(+=,==,<)��
													//		"mana"(+=,==,<)��
													//		"money"(+=,==,<)��
													//		"exp"(+=,==,<)��
													//		"pk"(+=,==,<)��
													//		"profession"(==, set, >=, <=)��
													//		"level"��(+=,==,<)��
													//		"force"��(+=,==,<)��
													//		"dexterity"��(+=,==,<)
													//		"speed"��(+=,==,<)��
													//		"health"��(+=,==,<)��
													//		"soul"��(+=,==,<)��
													//		"rank"��(==,<)��
													//		"rankshow"��(==,<)��
													//		"iterator"��(=, <=, +=, ==)��
													//		"crime" (==, set)
													//		"gamecard"(==, >=, <=)
													//		"gamecard2"(==, >=, <=)
													//		"xp"(+=)
													//		"metempsychosis"(==, <)
//													//      "nobility_rank"(==, <, +=, =)	// 
													//		"mercenary_rank"(==, <, +=)		// Ӷ���ȼ�
													//		"mercenary_exp"(==, <, +=)		// Ӷ������
													//		"exploit"(==, <, +=)			// ��ѫֵ
													//		"maxlifepercent"(+=,==,<)		// �������ǧ�ֱ� 
													//		"turor_exp"(==,<,+=,=)
													//		"tutor_level"(==,<,+=,=)
													//		"syn_proffer"(<,+=,=)	//���ɹ��׶�
													//		"maxeudemon"(<,+=,=)	//�����ٻ�������

		ACTION_USER_FULL			= 1002,			// ����ҵ����Լ�����"attr"��attr��ѡ"life","mana"
		ACTION_USER_CHGMAP			= 1003,			// �е�ͼ param "idMap nPosX nPosY bPrisonChk", bPrisonChkΪ��ѡ������ȱʡ�����Գ�����������Ϊ1���Գ�
		ACTION_USER_RECORDPOINT		= 1004,			// ���¼�� param "idMap nMapX nMapY"
		ACTION_USER_HAIR			= 1005,			// "color num"
													// "style num"
		ACTION_USER_CHGMAPRECORD	= 1006,			// �е�ͼ����¼��
		ACTION_USER_CHGLINKMAP		= 1007,			// �е�ͼ��NPC���ӵĵ�ͼ����Ҫ��NPC����

		ACTION_USER_TALK			= 1010,			// ����ҷ�MSGTALK��Ϣ��param��Ϊ��Ϣ����, dataΪƵ����
													// 	const unsigned short _TXTATR_NORMAL		=2000;
													// 	const unsigned short _TXTATR_ACTION		=_TXTATR_NORMAL+2;	// ����
													// 	const unsigned short _TXTATR_SYSTEM		=_TXTATR_NORMAL+5;	// ϵͳ
													// 	const unsigned short _TXTATR_TALK		=_TXTATR_NORMAL+7;	// ��̸
													// 	const unsigned short _TXTATR_GM 		=_TXTATR_NORMAL+11;	// GMƵ��
													//	const unsigned short _TXTATR_WEBPAGE 	=_TXTATR_NORMAL+105;	// ��URL
		ACTION_USER_MAGIC			= 1020,			// ��鷨����param����Ϊ��
													// "check type"(���ѧ��type���͵ķ���),
													// "check type level"(���ѧ��type���͵ķ������ҵȼ�Ϊlevel��),
													// "learn type"(���ѧ��type�෨�����ȼ�Ϊ0)��
													// "uplevel type"(��ҵ�type�෨����һ��)
													// "addexp type exp"(��ҵ�type�෨������exp�㾭��)
		ACTION_USER_WEAPONSKILL		= 1021,			// "check type level", ����������ܵ����ͺ͵ȼ����Ƿ�>=�ȼ�
													// "learn type level", ѧϰָ�����ͺ͵ȼ��ļ���
		ACTION_USER_LOG				= 1022,			// ����ָ����Ϣ��gm log�����봥������Ϣ�����ֺ�id��,��Ϣָ����param��
													// ���� "%s ����콣���񲢻�ñ�ʯ", param��%s���Ǳ��津������Ϣ��λ��
		ACTION_USER_BONUS			= 1023,			// ȡһ����Ʒ��
		ACTION_USER_DIVORCE			= 1024,			// ���
		ACTION_USER_MARRIAGE		= 1025,			// �������, �ѻ鷵��1��δ�鷵��0
		ACTION_USER_SEX				= 1026,			// �Ա���, �з���1��Ů����0
		ACTION_USER_EFFECT			= 1027,			// ����action�����︽��ָ����Ч��paramΪ"opt effect", opt֧��"self", "couple", "team", "target", effectΪ��Ч����
		ACTION_USER_TASKMASK		= 1028,			// task mask��ز�����paramΪ"opt idx", optΪ������֧��"chk", "add", "clr", idxΪ�����ţ�ȡֵ(0-31)
		ACTION_USER_MEDIAPLAY		= 1029,			// ý�岥��, param Ϊ"opt media", opt֧�� "play, broacast", "media"Ϊý���ļ���
		ACTION_USER_SUPERMANLIST	= 1030,			// ��ѯ��˫�б�, ��ʼֵ����TASK_ITERATOR�С�param="idNextTask number", idNextTask����һ��TASK��ֵ��number��ÿ���´������б��
		ACTION_USER_CHKIN_CARD		= 1031,			// ɾ��������ϵ���Ϸ����Ʒ�����һ����Ϸ����¼
		ACTION_USER_CHKOUT_CARD		= 1032,			// ���һ����Ϸ����Ʒ����ң�ɾ��һ����Ϸ����¼
		ACTION_USER_CREATEMAP		= 1033,			// ����һ�ŵ�ͼ�����ӵ���ҵ�home_id�ϣ���Ҫ��Ҷ���param="name owner_type owner_id mapdoc type portal_x portal_y reborn_map reborn_portal res_lev"��partalָ��ڵ����꣬res_lev��ʾ��ͼ�ȼ�(��������)��
		ACTION_USER_ENTER_HOME		= 1034,			// �ص��Լ��ļҡ�
		ACTION_USER_ENTER_MATE_HOME	= 1035,			// �ص���ż�ļҡ�
		ACTION_USER_CHKIN_CARD2		= 1036,			// ɾ��������ϵ���Ϸ��2��Ʒ�����һ����Ϸ��2��¼
		ACTION_USER_CHKOUT_CARD2	= 1037,			// ���һ����Ϸ��2��Ʒ����ң�ɾ��һ����Ϸ��2��¼
		ACTION_USER_FLY_NEIGHBOR	= 1038,			// �ڵ�ͼ���в���һ��_ROLE_NEIGHBOR_DOOR���͵�NPC��������������NPC����param="serial"��serial��ָdata3��ֵ��
		ACTION_USER_UNLEARN_MAGIC	= 1039,			// ת��ʱ����ȴħ�����ܣ��ü��ܽ��������١����򡱡�param="type1 type2 ..."������һ�����������20��������
		ACTION_USER_REBIRTH			= 1040,			// ת���������ת�����ߵȼ������ˣ���ʧ�ܡ��������Ƿ��Ѿ�תְ��ְҵҪ�󡢵ȼ�Ҫ���Զ��޸����ְҵ���ȼ�������װ���ȼ������·��������param="nProf nLook"
													// ���¹���������ACTION��ɣ���������15��40��100���ľ�ְ���������ｱ������ʱ�سǣ����ܽ�����
		ACTION_USER_WEBPAGE			= 1041,			// ֪ͨ�ͻ��˴���ҳ��param="http://....."
		ACTION_USER_BBS				= 1042,			// ��BBS������У����һ��SYSTEMƵ������Ϣ��������Ϊ������֡���ҪUSER����ÿ��USER������һ����param����Ϣ���ݡ�
		ACTION_USER_UNLEARN_SKILL	= 1043,			// ת��ʱ����ȴ�����������ܣ��ü��ܽ��������١����򡱡�
		ACTION_USER_DROP_MAGIC		= 1044,			// ת��ʱ��ɾ��ħ�����ܡ�param="type1 type2 ..."������һ�����������20��������
		ACTION_USER_OPEN_DIALOG		= 1046,			// ֪ͨ�ͻ��˴�һ�����档data=idDialog��param="task_id0 task_id1 task_id2 task_id3 ..."��������param�����20��task_id, task_id����Ϊ0, ����ͻ���ѡ����һ��TASK����paramʱ���ͻ���ֻ���ϴ����ͻ��˿ɴ�����TASK������paramʱ��cq_task.client_active����Ϊ0��
		ACTION_USER_CHGMAP_REBORN	= 1047,			// ����������㡣
//		ACTION_USER_ADD_WPG_BADGE	= 1048,			// �����PK������������ҵ��ĵ�һ������������ӡ�����Ʒ�����ǿɵ��ӵġ����ֻ��������
		ACTION_USER_DEL_WPG_BADGE	= 1049,			// ɾ��������PK�����
		ACTION_USER_CHK_WPG_BADGE	= 1050,			// ����������ֻ��һ��param���͵���Ʒ(����ֻ����һ��)��û��������PK�������paramΪ�ձ�ʾ�������κ���PK�����
		ACTION_USER_TAKESTUDENTEXP	= 1051,			// ��ȡͽ�ܹ��׵ľ��顣��ҷ���pszAcceptָ����Ҫ��ȡ�ľ���ֵ���Զ��۳���ʦ���顣

		ACTION_USER_CHGTO_MAINMAP	= 1052,			// ������ͼ�ĸ���㸴��
		ACTION_USER_CHGTO_RANDOMPOS	= 1053,			// ��������ɵ���ǰ��ͼ������һ�����꣨�õ㲻�������룩


		//---����ϵͳ����¼�����ϸ��---begin

		ACTION_USER_TASK_MANAGER	= 1080,			/////////////////////////////////////////////////
													////data:�����ţ�
													//param: 'new' (Ϊ�����¼�¼)
													//       'delete' (ɾ����¼)
													//		 'isexit' (�����Ƿ����)
													/////////////////////////////////////////////////
		
		ACTION_USER_TASK_OPE		=1081,			/////////////////////////////////////////////////
													//data: �����ţ�  ��data == -1 ,������Ĳ�������� findnext ���е�
													//param: 'ope opt data',  data(ֵ)
													//		 ope(phase)		 opt(>=, ==, +=,=) ������׶β���										
													//		 ope(completenum) opt(>=, ==, +=,=) ��������ɴ�������		
													//       ope(begintime)	 opt(>=, ==, +=,=,reset) ������ʼʱ�����, ���� += ʱ ����Ϊ����������">=,==,="ʱ��"yyyy-mm-dd hh:mm:ss"Ϊ��ʽ												
													//                           reset��ʾ ������Ŀ�ʼʱ������Ϊ��ǰʱ��
		ACTION_USER_TASK_LOCALTIME = 1082,          /////////////////////////////////////////////////////////
													//data: �����ţ�      
													//param: �������� , ��ǰʱ��������ʼʱ��Ƚϵ�action������ǰʱ��������Ŀ�ʼʱ��֮�� ���� param ���򷵻�true.���򷵻�false
													//////////////////////////////////////////////////////////////////////

		ACTION_USER_TASK_FIND		= 1083,			//�����������в�ѯ ,��¼�ǰ��� userid , taskid ����ļ���
													//param: 'find taskid phase completenum ';��������ID���׶Σ���ɴ�����ѯ�����¼; phase �� cocompletenumͬʱΪ-1ʱ��ֻ��ѯ����taskid�ļ�¼
													//		 'findnext'	;��ѯ��һ����¼
		//---����ϵͳ����¼�����ϸ��---end

		
		// team part. �� û�ж���ʱ���᷵�� false������ACTION�����ɶӳ�������
		// ��������Ϊÿ����Ա(ͨ���������ӳ�)����Ա������һ����Χ�ڡ�
		// ע�⣺�������еĶ�Ա��trueʱ���ŷ���true�����򷵻�false 
		// �� ---------------------------------------------------------------
		ACTION_TEAM_BROADCAST		= 1101,			// ���ڶ���Ƶ���й㲥һ����Ϣ��param=��Ϣ��
		ACTION_TEAM_ATTR			= 1102,			// ���������Ա���ԡ�
													// param="field opt data", 
													// field="money"(+=��<��>��==), 
													// field="level"(<��>��==), 
													// field="count"(���ӳ��Ķ�Ա������<��==), 
													// field="count_near"(���ӳ��Ķ�Ա����������ͼ�У�������ţ�<��==), 
													// field="mate"(ֻ��Ҫfield���������), 
													// field="friend"(ֻ��Ҫfield���������), 
		ACTION_TEAM_LEAVESPACE		= 1103,			// ��鱳��ʣ��ռ�, param="space weight packtype"��
													// packtypeΪ��Ҫ���ı������ͣ�ȡֵ��Χ50~53
		ACTION_TEAM_ITEM_ADD		= 1104,			// �����Ʒ��data=itemtype_id
		ACTION_TEAM_ITEM_DEL		= 1105,			// ɾ����Ʒ��data=itemtype_id
		ACTION_TEAM_ITEM_CHECK		= 1106,			// �����Ʒ��data=itemtype_id
		ACTION_TEAM_CHGMAP			= 1107,			// �������(�����ӳ�)��������ͬһ����ͼ�������������˱�����š�param="mapid x y"
		
		ACTION_TEAM_CHK_ISLEADER	= 1501,			// ����Ƿ�Ϊ�ӳ�������Ҫ����
		ACTION_USER_LIMIT			= 1999,

		// event part, need not any ptr --------------------------------------------------------------------------
		ACTION_EVENT_FIRST			= 2000,
		ACTION_EVENT_SETSTATUS		= 2001,			// ���õ�ͼ״̬��param="mapid status_bit data", status_bit = { STATUS_WAR=1, }, data=0��1��
		ACTION_EVENT_DELNPC_GENID	= 2002,			// (����)ɾ��MONSTER��param="idMap idGen"��
		ACTION_EVENT_COMPARE		= 2003,			// �Ƚϸ������ԡ�"data1 opt data2"��data1��data2Ϊ��%��ͨ�ò���, �����������Ƚϡ�opt��ѡ"=="��"<"��"<="
		ACTION_EVENT_COMPARE_UNSIGNED	= 2004,			// �Ƚϸ������ԡ�"data1 opt data2"��data1��data2Ϊ��%��ͨ�ò���, ���޷������Ƚϡ�opt��ѡ"=="��"<"��"<="
		ACTION_EVENT_CHANGEWEATHER	= 2005,			// �޸�ָ��REGION��������param="idMap idRegion Type Intensity Dir Color KeepSecs", Type, Intensity=0~999, Dir=0~359, Color=0x00RRGGBB, KeepSecs=seconds
		ACTION_EVENT_CREATEPET		= 2006,			// ����һ��MONSTER��param="nOwnerType idOwner idMap nPosX nPosY idGen idType nData szName", ����7������, ����accept�������������name������generator���ڿ��ƹ�����Χ��cq_generator�е�type�����塣idOwnerΪ0ʱ�������̡�
		ACTION_EVENT_CREATENEW_NPC	= 2007,			// ����һ��NPC��param="name type sort lookface ownertype ownerid  mapid posx posy  life base linkid  task0 task0 ... task7  data0 data1 data2 data3 datastr"������9��������
		ACTION_EVENT_COUNTMONSTER	= 2008,			// ���ͬ��ͼ��MONSTER������param="idMap field data opt num", field="name"(������)��"gen_id"(������), data=Ҫͳ�Ƶ����ֻ�����, opt="<"��"=="��
		ACTION_EVENT_DELETEMONSTER	= 2009,			// ɾ��ĳ��ͼ��MONSTER��param="idMap type data name", �����������������data��Ϊ0��ͬʱƥ��data, �����name��ͬʱƥ��name��
		ACTION_EVENT_BBS			= 2010,			// ��BBS������У����һ��SYSTEMƵ������Ϣ��������Ϊ��SYSTEM����param����Ϣ���ݡ�
		ACTION_EVENT_ERASE			= 2011,			// ɾ��ָ��NPC���޶�̬NPC��ע�⣺ɾ���󣬲�Ҫ�ٶԴ���NPC���в�����param="idMap type": ɾ��ָ����ͼ����������Ϊtype��NPC��
		ACTION_EVENT_LIMIT			= 2099,

		// event part, need not any ptr --------------------------------------------------------------------------
		ACTION_TRAP_FIRST			= 2100,
		ACTION_TRAP_CREATE			= 2101,			// ����һ�����塣param="type look owner_id map_id pos_x pos_y data"��
		ACTION_TRAP_ERASE			= 2102,			// ɾ��һ�����塣param="", ɾ����ǰ���塣ע�⣺ɾ����Ҫ�ٲ��������塣
		ACTION_TRAP_COUNT			= 2103,			// �������Ϊtype����������, С��count����true��param="map_id pos_x pos_y pos_cx pos_cy count type"��
		ACTION_TRAP_ATTR			= 2104,			// �޸����������(������)��param="id field opt num"��field: "type"(opt: "="), "look"(opt: "=")��
		ACTION_TRAP_LIMIT			= 2199,

		// wanted list part  --------------------------------------------------------------------------
		ACTION_WANTED_FIRST			= 3000,
		ACTION_WANTED_NEXT			= 3001,			// ��Ѱ�¸����ͣ���idxд��TASK_ITERATOR
		ACTION_WANTED_NAME			= 3002,			// ��ҷ���pszAcceptָ��������������, ��ACTION_WANTED_NEW���á�
		ACTION_WANTED_BONUTY		= 3003,			// ��ҷ���pszAcceptָ������ACTION_WANTED_NEW���á�
		ACTION_WANTED_NEW			= 3004,			// ͨ��CUser::m_WantedInfo�����µ����ͼ�¼������2��action����ʹ�á�
		ACTION_WANTED_ORDER			= 3005,			// ��ȡpszAccept��ָ��������
		ACTION_WANTED_CANCEL		= 3006,			// ��2���ļ�Ǯȡ��pszAccept��ָ��������
		ACTION_WANTED_MODIFYID		= 3007,			// ��ҷ���pszAcceptָ���޸ĵ�����id��
		ACTION_WANTED_SUPERADD		= 3008,			// ��ҷ���pszAcceptָ��׷�����͵Ľ�Ǯ����ACTION_WANTED_ID����ʹ�á�
		ACTION_POLICEWANTED_NEXT	= 3010,			// ��Ѱ�¸��ٷ����ͣ���idxд��TASK_ITERATOR
		ACTION_POLICEWANTED_ORDER	= 3011,			// �Ұ�(pszAccept��ָ�����)
		ACTION_POLICEWANTED_CHECK	= 3012,			// ��鴥�����Ƿ񱻹ٸ�ͨ��
		ACTION_WANTED_LIMIT			= 3099,	
		
		// ghost gem magic part  ----------------------------------------------------------------------------------
		ACTION_MAGIC_FIRST			= 4000,
		ACTION_MAGIC_ATTACHSTATUS	= 4001,			// ׷��״̬��szParam="status power secs times"		                                          	
		
		ACTION_MAGIC_ATTACK			= 4002,			// ħ��������data=magictype, szParam="magiclevel"
													// Ҫ��magictype���д�����Ӧ������
													// Ŀǰ֧�ֵ�ħ�������У�
													//		MAGICSORT_DETACHSTATUS
													//		MAGICSORT_STEAL
		ACTION_MAGIC_LIMIT			= 4099,

};

