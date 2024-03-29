#ifndef EN_RES_H
#define EN_RES_H
//---------------------------------------------------------------------------

//General
#define	STR_OPEN					"Open"
#define	STR_CLOSE					"Close"
#define	STRING_BET_WIN				"%s红光满面，双眉带彩，玩骰子赢了%d金币！"

//General Error
#define	STR_ERROR					"Error"
#define	STR_DELETE_FAILED			"Failed to delete!"
#define	STR_ERROR_ILLEGAL_NAME2		"Error: Illegal name!"

#define STR_TOOMUCH_MONEY			"You have too much money on you to pick it up."
#define STR_TOOMUCH_MONEY_TO_DRAW	"You have too much money, you can't take it anymore."
#define STR_TOOMUCH_MONEY_SAVED		"There is too much money in the warehouse."

// Login
#define	STR_LOGIN_ANOTHER			"Someone is logging in to this account."
#define	STR_LOGIN_AGAIN				"This account is already logged in."
#define	STR_LOGIN_ISP_FAIL			"Fail to log into ISP payment system. Curently, your account is charged."

#define	STR_KICKOUT_ALL_AFTER		"开始处理kickoutall，服务器禁止登录。%d秒之后，所有玩家退出。"
#define	STR_KICKOUT_ALL				"开始处理kickoutall，服务器禁止登录，所有玩家退出中 . . ."

//Action
#define STR_ACTION_USER_FLYTOMAINMAP_ERROR	"The main map does not exist, and the city roll cannot be used!"

#define	STR_YOUR_CANNOT_WALK		"You cannot walk！"

// Chatroom
#define STR_CHATROOM_NAME								"Chatroom %d"
#define STR_CHATROOM_CANNOT_INMOREROOM					"Cannot enter multiple chat rooms at the same time!"
#define STR_CHATROOM_CANNOT_INMOREROOM_FORNOMONEY		"Not enough money to enter the chat room!"
#define STR_CHATROOM_WELCOME							"%s, welcome to the chat room %s. This room is managed by %s."
#define STR_CHATROOM_LEAVE								"%s left the chat room %s."
#define STR_CHATROOM_CANAPPLYMANAGER					"The chat room manager %s has not logged in recently. Player applications for manager are now open."
#define STR_CHATROOM_MEMBERFULL							"This chat room is full!"
#define STR_CHATROOM_ROOMFEE_MODIFY						"The current chat room fee has been changed to %d gold."

//Items General
#define STR_NOT_DISCARDABLE			"This item cannot be discarded."
#define STR_NOT_SELL_ENABLE			"This item cannot be sold."
#define	STR_FULLBAG_NO_MORE	        "阁下行囊已满，无法放入更多物品。"
#define STR_ITEMBAG_FULL			"Your inventory is full, unable to get item."
#define STR_DROPITEM_PROMPT			"您丢弃了%s ！"
#define	STR_REPAIR_FAILED	        "不能修理!"
#define	STR_REPAIR_NO_MONEY_d	    "修理需要花费%d个金币，金币不足无法修理！"

//Item Identify
#define STR_IDENT_NORMAL					"鉴定成功，得到%s"
#define STR_IDENT_QUALITY_ONE				"鉴定成功，得到良品 %s"
#define STR_IDENT_QUALITY_TWO				"鉴定成功，得到上品 %s"
#define STR_IDENT_QUALITY_THREE				"鉴定成功，得到精品 %s"
#define STR_IDENT_QUALITY_FOUR				"鉴定成功，得到极品 %s"
#define STR_ACTION_IDENT_SUCC				"鉴定成功！"
#define STR_ACTION_IDENT_FAIL				"鉴定失败！"
#define STR_ACTION_IDENT_FAIL_DISAPPEAR		"鉴定失败，物品已损坏！"


// Upgrade Equipment Level - NA
#define STR_UPEQUIPLEVEL_FAIL_NOTYPE		"★ Failed to upgrade equipment level! No corresponding equipment!★"
#define STR_UPEQUIPLEVEL_FAIL				"★ Failed to upgrade equipment level!★"
#define STR_UPEQUIPLEVEL_SUCC				"★ Upgrade equipment level successfully!★"
#define STR_UPEQUIPLEVE_SUCC				"★ Upgrade the equipment successfully, congratulations! Hope to continue working hard!★"
#define STR_UPEQUIPLEVE_FAIL				"★ Failed to upgrade the level of the equipment. This time you are out of luck. Please continue!★"

// Upgrade Equipment Quality - NA
#define STR_QUALITY_UPGRADE_SUCCESS         "★ Upgrade equipment quality successfully, congratulations! Keep working hard!★"
#define STR_QUALITY_UPGRADE_FAILED          "★ Failed to upgrade the quality of the equipment. Your luck is not very good this time, please keep working hard!★"
#define STR_QUALITY_UPGRADE_MAXLEVEL        "★ Failed to upgrade equipment quality, your equipment is already the highest quality!★"
#define STR_ITEM_CHANGETYPE_FAILED          "★ Upgrade of equipment quality failed, there is no corresponding type!★"
#define STR_ITEM_CHANGEADDITION_FAILED      "★ Failed to add equipment attributes, there is no corresponding type ★"

//Eudemon Ghost Level - NA
#define STR_GHOSTLEVEL_EUDEMON_NOTCOMPETENT	"★ Failed to upgrade the equipment's soul level, fantasy monsters are not eligible!★"
#define STR_GHOSTLEVEL_SUCCESS				"★ Congratulations on your success in upgrading the equipment's Demon Soul level! Hope to continue working hard!★"
#define STR_GHOSTLEVEL_FAILED				"★ Upgrading the equipment's Demon Soul level failed. This time you are out of luck. Please continue!★"
#define STR_GHOSTLEVEL_FAILED_NOTYPE		"★ No corresponding data!★"

//Gems - NA
#define STR_EMBED_SUCC	"Embedded successfully!"
#define STR_EMBED_FAIL	"Embedding failed!"

//Combat
#define STR_HITRATE_ADD				"技能启动：%d秒内命中率增加%d倍。"
#define STR_DEFENCE_ADD				"技能启动：%d秒内防御力增加%d倍。"
#define STR_ATTACK_ADD				"技能启动：%d秒内攻击力增加%d倍。"
#define STR_HITRATE_ADD2			"技能启动：%d秒内命中率增加%d。"
#define STR_DEFENCE_ADD2			"技能启动：%d秒内防御力增加%d。"
#define STR_ATTACK_ADD2				"技能启动：%d秒内攻击力增加%d。"
#define STR_SUPER_ATK_ADD			"技能启动：%d秒内攻击力增加%d。"
#define STR_SUPER_DEF_ADD			"技能启动：%d秒内防御力增加%d。"
#define STR_SUPER_MATK_ADD			"技能启动：%d秒内魔法攻击力增加%d。"
#define STR_SUPER_MDEF_ADD			"技能启动：%d秒内魔法防御力增加%d。"
#define STR_TEAM_MAGIC				"%s 发动。"
#define STR_TEAM_MAGIC2				"%s 发动，效果增加%d%%。"
#define STR_NOT_ENOUGH_POTENTIAL	"您的潜能值不足，无法使用结界。"

//Syndicate
#define	STR_SYNDICATE_LEADER		"Chief of Knights"
#define	STR_SYNDICATE_LEADER2		"Deputy Chief of Knights"
#define	STR_SYNDICATE_LEADER3		"Head of the Guards"
#define	STR_SYNDICATE_LEADER4		"Deputy Head of the Guards"
#define	STR_SYNDICATE_LEADER5		"Acting head of the guard"
#define	STR_SYNDICATE_MEMBER		"Knight"
#define STR_SYNDICATE_PK_MODE       "Knights PK mode, you can PK all players except this group and the Alliance Knights."
#define STR_SYN_APPLYATTACKSYN_SUCCESS        "申请攻打该城市成功，请三日后来攻城！"
#define STR_SYN_APPLYATTACKSYN_FAIL          "申请攻打该城市成功失败，阁下的帮派条件不符合！"
#define STR_SYN_APPLYATTACKSYN_HASBEENAPPLIED "The application for the attack on the city was unsuccessful.Someone has already applied for the attack!"
#define STR_SYNWAR_ANNOUNCE			"%d-%d-%d 20:00:00 开始攻打帮派 %s。"
#define STR_SYNWAR_ANNOUNCE2		"%d-%d-%d 20:00:00 %s 帮派开始攻打本帮派。"
#define STR_TOO_LOWER_SYN_MONEY		"The Knights Fund is insufficient and the feature has been turned off."
#define STR_SYN_SETDRESS_SUCC				"设置帮派服装成功！"
#define STR_SYN_PUTONDESS_ERR				"必须是团长才能下穿帮派服装的命令！"
#define STR_SYN_CREATESUBSUB_ERR			"不符合条件或分队已经满了！"
#define STR_SYN_DEMISE_SUCC					"您将团长职位禅让给了%s"
#define STR_SYN_DEMISE_CON					"恭喜您成为了%s军团团长"
#define STR_SYN_DEMISE_PROMPT				"%s出任%s军团团长一职"
#define STR_SYN_SETSUBLEADER_ERR			"%s等级不足或对军团的贡献不够，不能出任该职务。"
#define STR_SYN_SETSUBLEADER_SUCC			"您册封了%s为%s分团副团长一职"
#define STR_SYN_SETSUBLEADER_CON			"恭喜您成为了%s分团副团长"
#define STR_SYN_SETSUBLEADER_PROMPT			"%s出任%s分团副团长一职"
#define STR_SYN_SETSUBSUBLEADER_SUCC		"您册封了%s为%s分队队长一职"
#define STR_SYN_SETSUBSUBLEADER_CON			"恭喜您成为了%s分队队长"
#define STR_SYN_SETSUBSUBLEADER_PROMPT		"%s出任%s分队队长一职"
#define STR_SYN_CREATE_SUBSUBSYN_ERROR		"创建分队，必须是分团的团长！"
#define STR_SYN_CANNOT_UPMEMBERLEVEL        "升级帮派成员等级失败，你的条件还不符合！"
#define STR_SYN_SUCCESS_UPMEMBERLEVEL        "升级帮派成员等级成功，希望再接再厉！"
#define STR_SYN_APPLYATTACKSYN_SUCCESS        "申请攻打该城市成功，请三日后来攻城！"
#define STR_SYN_APPLYATTACKSYN_FAIL          "申请攻打该城市成功失败，阁下的帮派条件不符合！"
#define STR_SYN_APPLYATTACKSYN_HASBEENAPPLIED "申请攻打该城市成功失败，已经有人申请攻打了！"
#define STR_SYN_APPLYKICKOUT_MEMBER         "已经向帮主发出开除请求！"
#define STR_SYN_SETSUBLEADER_NOPROFFER		"不能设置，贡献度不足！"
#define STR_SYN_APPLY_JOIN_FAILED			"请找团长或副团长加入！"
#define STR_SYN_NOTENOUGH_PROFFER_LEAVE		"您的军团贡献度小于%d，不允许退团！"
#define STR_SYN_LEAVE_s						"%s 退出了军团！"
#define	STR_SYN_FULL				"错误：骑士团人数已满!"
#define	STR_JOIN_SYN_FAILED			"错误：加入失败!"
#define	STR_INVALID_PET_NAME		"错误：不允许的名字!"
#define STR_JOIN_SYN_s				"恭喜您成为 %s 军团团员。"
#define	STR_KICKOUT_MEMBER_s		"%s被开除出了%s军团。"
#define	STR_KICKOUT_ME_s			"你被%s从骑士团中开除。"
#define STR_SYN_ALLY_s				"恭喜 %s 军团与 %s 军团结为兄弟军团。"
#define STR_SYN_CLEAR_ALLY1_s		"与 %s 军团解除盟友之约。"
#define STR_SYN_CLEAR_ALLY2_s		"%s 军团与您的军团解除盟友之约！"
#define STR_SYN_ENEMY_s				"%s 军团将您的军团列为敌对军团。"
#define STR_SYN_CLEAR_ENEMY_s		"%s 军团将与您的军团解除敌对状态。"
#define STR_TOO_LOWER_SYN_MONEY		"骑士团基金不足，该功能已关闭。"
#define STR_SYN_AMOUNT_LIMIT        "骑士团人员不足，即将被强制解散，请尽快补充人员"
#define STR_SYN_MONEY_LIMIT         "骑士团资金不足，即将被强制解散，请尽快补充资金"
#define	STR_APPLY_ALLY_FAILED		"双方必须是骑士团团长!"
#define	STR_TOP_LIST_dsd			"Rank:%d Name:%s(%d)"

//Team
#define	STR_TEAM_MONEY_s			"Money picking switch %s"
#define	STR_TEAM_ITEM_s				"Pickup switch %s"
#define STR_TEAM_STATUS_POWER_INC	"Enchantment effect increased by %d %%."
#define STR_TEAM_STATUS_POWER_DEC	"Enchantment effect decreased by %d %%."
#define STR_TEAM_STATUS_DISAPPEAR	"The enchantment effect disappears."
#define	STR_GM_NO_TEAM	            "【GM】不能进行队伍操作。"
#define	STR_TEAMMATE_CANNOT_CREATE	"[队伍]您已经在队伍中了，不能创建新队伍。"
#define	STR_CREATE_TEAM_FAILED	    "[队伍]您创建队伍失败。"
#define	STR_INTEAM_NOJOIN		    "[队伍]您已经有队伍了。不能申请加入新队伍。"
#define	STR_NO_APPLICANT		    "[队伍]没有找到申请对象。"
#define	STR_NO_TEAM					"[队伍]您所申请的对象没有创建队伍。"
#define	STR_FORBIDDEN_JOIN	        "[队伍]对方队伍禁止加入了。"
#define	STR_TEAM_FULL			    "[队伍]您的所申请的队伍人数已满。"
#define	STR_NO_CAPTAIN_CLOSE	    "[队伍]申请对象不是队长，请向队长提出申请。"
#define	STR_JOIN_REQUEST_SENT	    "[队伍]已经发出加入队伍请求。"
#define	STR_INVI_SENT			    "[队伍]加入队伍申请已经提交，请等待回应。"
#define	STR_NO_TEAM_TO_INVITE	    "[队伍]您没有队伍，怎能接受别人加入队伍？"
#define	STR_NOT_CAPTAIN_INVITE	    "[队伍]您不是队长，怎能接受别人加入队伍？"
#define	STR_YOUR_TEAM_FULL		    "[队伍]您的队伍人数已满。"
#define	STR_APPLICANT_NOT_FOUND	    "[队伍]没有找到发出申请的玩家。"
#define	STR_HAVE_JOIN_TEAM	        "[队伍]您已经加入队伍了，不能同时加入另外一个。"
#define	STR_NOT_TO_JOIN	            "[队伍]对方没有发出加入申请，您不能接受对方。"
#define	STR_NOTEAM_TO_INVITE	    "[队伍]您没有队伍，怎能邀请别人加入队伍？"
#define	STR_TEAM_CLOSED	            "[队伍]您不允许其他人加入队伍，操作失败！"
#define	STR_NOT_CAPTAIN_ACCEPT	    "[队伍]您不是队长，怎能邀请别人加入队伍？"
#define	STR_INVITED_NOT_FOUND	    "[队伍]没有找到要邀请的玩家。"
#define	STR_HAS_IN_TEAM	            "[队伍]您所邀请的对象的已经有队伍了。"
#define	STR_INVITE_SENT				"[队伍]已经发出邀请加入队伍请求。"
#define	STR_SENT_WAIT				"[队伍]邀请已经发出，请等待。"
#define	STR_INTEAM_NOACCEPT			"[队伍]您已经有队伍了，不能接受邀请加入新队伍。"
#define	STR_INVITER_NOT_FOUND	    "[队伍]没有找到邀请者。"
#define	STR_NOT_CREATE_TEAM		    "[队伍]对方还没有组队。"
#define	STR_HIS_TEAM_FULL		    "[队伍]对方的队伍已经满员了。"
#define	STR_NOT_BE_INVIITED	  	    "[队伍]对方没有向您发出加入队伍的邀请，操作失败。"
#define	STR_NO_TEAM_TO_LEAVE	    "[队伍]您还不是队员，不能退出队伍。"
#define	STR_NO_TEAM_TO_DISMISS	    "[队伍]您还没有队伍，不能解散队伍。"
#define	STR_NOT_CAPTAIN_DISMISS	    "[队伍]您不是队长，不能解散队伍。"
#define STR_INVITED_IS_DEAD			"[队伍]不能邀请亡灵状态下玩家加入队伍。"
#define STR_APPLIED_LEADER_DEAD		"[队伍]不能加入亡灵的队伍。"

//Eudemons
#define STR_EUDEMON_LOW_LEVEL		"错误：幻兽等级不足%d级！"
#define STR_EUDEMON_CANNOT_EVOLVE	"Mistake: Phantom cannot evolve!"

// Booths
#define STR_BOOTH_FULL				"Your stall is full and no more items can be placed."

//Locks
#define	STR_SETLOCK					"setlock"
#define	STR_UNLOCK					"unlock"
#define	STR_CLEARLOCK				"clearlock"
#define	STR_SETLOCK_HELP			"设置“保护锁”密码之前不能有旧的密码，密码必须为 6 ~ 9 位整数，不能使用字母或符号，也不能使用过于简单的密码。使用方法：/setlock 密码"
#define	STR_UNLOCK_HELP				"临时打开“保护锁”，下线会自动加锁。使用方法：/unlock 密码"
#define	STR_CLEARLOCK_HELP			"永久清除“保护锁”密码。使用方法：/clearlock 旧密码"
#define	STR_SETLOCK_OK				"已设置“保护锁”的密码。可使用“/unlock 密码”临时打开保护锁，也可使用“/clearlock 旧密码”永久清除保护锁。"
#define	STR_SETLOCK_FAIL			"设置“保护锁”失败! 设密码之前不能有旧的密码，密码必须为 6 ~ 9 位整数，不能使用字母或符号，也不能使用过于简单的密码。"
#define	STR_UNLOCK_OK				"已打开“保护锁”，下线后会自动加锁。"
#define	STR_CLEARLOCK_OK			"已永久清除“保护锁”，该帐号不再受到“保护锁”的保护。如需重新设置保护锁，请使用“/setlock 密码”。"
#define	STR_LOCKKEY_DENY			"Please open the 'protection lock' first. How to use: / unlock password"

//Stealing
#define STR_AVOID_STEAL				"With the help of anti-theft gems, you have escaped the theft of %s."
#define STR_STOLEN					"You were stolen by %s."

//  OLD - Unsorted
#define DRAGON_BALL_DROP			"A dragon ball drop from the monster killed by %s."
#define EXPLOST_PAYBY_SYNFUND		"%u exp lost reduce by syndicate fund."
#define MALE_MATE_LOGIN				"Your husband is now online."
#define FEMALE_MATE_LOGIN			"Your wife is now online."
#define NOMATE_NAME					"None"
#define TITILE_NONE					"None"
#define SYNNAME_NONE				"None"
#define	ACTIONSTR_NONE				"None"
#define	STR_DESTROY_SYNDICATE_SOON	"Your guild's fund has been used up. Please replenish the guild fund or your will be terminated forcedly."
#define	STR_TARGET_OFFLINE			"The target is not on-line."
#define	STR_SYNDICATE_COMBINESUB_ss	"Guild %s is merged by %s."
#define	STR_SUPERMAN_BROADCAST_sddd	"%s 武艺精湛，在爆发时间内杀死%d只怪物，荣登KO排行榜的第%d名，奖励KO时间%d秒。"
#define	STR_NEXTEQP_OVERLEV			"Level requirement of the new equipment is higher than your level!"
#define	STR_DISPATCHXP_s			"%s roared, and the teammates' XP boosts immediately1"
#define	STR_BOOTH_BUY_sds			"%s spent %d silvers to buy your %s."
#define	STR_DISABLE_LAY_SYNTRANS	"This kind of NPC is not allowed to place here!"
#define	STR_ITEM_LEV_TOO_HIGH		"Level reqirement of the equipment is much too high!"
#define	STR_TEAM_HUNT				"Notorious %s was finally hunted down by the detective team headed by %s!"
#define	STR_FOND_WANTED				"The wanted target [%s] is found! "
#define	STR_FOND_POLICEWANTED		"The governmental wanted target [%s] is found! "
#define	STR_CANT_STORAGE			"This item cannot be deposited!"
#define	STR_SYN_FULL				"Error: the amount of guild members is full!"
#define	STR_JOIN_SYN_FAILED			"Error: failed to join!"
#define	STR_INVALID_PET_NAME		"Error: forbidden name!"
#define	STR_KICKOUT_MEMBER_s		"%s did not abide by the rules of the guild and was driven out of the guild."
#define	STR_KICKOUT_ME_s			"You have been dispelled from the guild by %s."
#define	STR_NO_ENOUGH_POWER			"You do not have enough mana to broadcast!"
#define	STR_NO_ENOUGH_LEVEL			"Your level is not high enough to broadcast!"
#define	STR_NO_BONUS				"Sorry. No prize available or the prize has not been confirmed in the prize claiming web page."
#define	STR_WARNING_CRASH			"Warning: the command is for local test only, or the server may collape!"
#define	STR_CAN_STAND				"You cannot stop in the destination!"
#define	STR_SET_MAX_PLAYERS_u		"Max logged in users allowed changed to: %u"
#define	STR_SHOW_PLAYERS_uu			"Current online players: %u, max online players: %u"
#define	STR_CAN_NOT_TALK			"You have been stricken the vital point and cannot talk temporarily!"
#define	STR_ARRESTMENT_PK_MODE		"Restrictive PK mode. You can only attack monsters, black-name and red-name players."
#define	STR_TEAM_PK_MODE			"Team PK mode. You can attack monsters and players except for your teammates."
#define	STR_SAFE_PK_MODE			"Peace mode. You can only attack monsters and won't hurt other players."
#define	STR_FREE_PK_MODE			"Free PK mode. You can attack anyone."
#define	STR_NEED_PICK				"You must use a pecker to mine."
#define	STR_SYNDICATE_DESTROY_s		"Guild %s has been terminated."
#define	STR_SYNDICATE_CREATE_ss		"Congratulations! %s has set up %s successfully."
#define	STR_SYN_LEADER_LOSE_uss		"Guild [%u]'s guild leader [%s] disappeared and [%s] took the place."
#define	STR_DONATE_ssd				"%s donated %s %d Oz."
#define	STR_SYN_WAR_END				"Guild battle ended!"
#define	STR_SYN_WAR_START			"Guild battle started!"
#define	STR_GOT_WIN_s				"%s has won!"
#define STR_CHARACTER_CREATED		"Your character was successfully created! Please log back in to begin."
#define	STR_ERROR_DUPLICATE_NAME	"Error: a character with this name already exists!"
#define	STR_ERROR_ILLEGAL_NAME		"Error: the name of the character is invalid!"
#define	STR_ERROR_ILLEGAL_NICKNAME	"Error: the nickname of the character is invalid!"
#define	STR_ERROR_ILLEGAL_TYPE		"Error: the character type is not valid!"
#define	STR_ERROR_ILLEGAL_STAT		"Error: the allocated stats are not valid. Please allocate all points!"
#define	STR_ERROR_ILLEGAL_PASSWORD	"Error: invalid password!"
#define	STR_ERROR_ILLEGAL_ACCOUNT	"Error: invalid account ID!"
#define	STR_ERROR_SERVER_FULL		"Error: the server is full. Please re-log in later!"
#define	STR_ERROR_LOWER_VERSION		"Error: invalid version number. Please update your client!"
#define	STR_ERROR_VERSION			"Error: invalid version number!"
#define	STR_FEW_FEE_NOTIFY			"You month card will expire on %s. Please recharge your account soon."
#define	STR_ACCOUNT_NOFEE			"Your account has not been recharged."
#define	STR_FEETYPE_KNOWN			"Payment type: unknown."
#define	STR_FEETYPE_HOUR			"Payment type: hour card. Reminding hours: %d.%d."
#define	STR_FEETYPE_MONTH			"Payment type: month card. Expired on:  %d(year) %d(month) %d(day)"
#define	STR_FEETYPE_BARHOUR			"Payment type: internet cafe point card."
#define	STR_FEETYPE_BARMONTH		"Payment type: internet cafe point card. Licensed amount: %d."
#define	STR_FEETYPE_ISP				"Payment type: ISP payment system."
#define	STR_FEETYPE_FREE			"Payment type:  free test."
#define	STR_SHUTDOWN_NOTIFY			"Server maintenance for ten minutes. Please log off immediately to avoind data lost."
#define	STR_NONSUCH_TRADE_sssu		"[Trade] Trading superior item. Player [%s] gave player [%s] [%s][%u]"
#define	STR_NOT_ENOUGH_MONEY	    "You do not have enough money."	
//#define	STR_NOT_ENOUGH_MONEY	    "You don't have %d silvers!"
#define	STR_DIE_FORGIVE	            "He that dies pays all debts. Can't you forgive him?"	
#define	STR_DIE_STOP_ATTACK	        "The target is dead. Move on."	
#define	STR_ATTACK_POLICE	        "You are attempting to attack the police. Please behave yourself."	
#define	STR_KILLING_EXPERIENCE	    "%u extra experience points gained for killing."	
#define	STR_KILLING_EXPEX			"%u extra experience points gained for killing."	
#define	STR_BAG_FULL	                                     "Your bag is full!"
#define	STR_TRADE_SUCCEED	        "Trading succeeded."	
#define	STR_TRADE_FAIL	                     "Trading failed!"	
#define	STR_USE_ITEM	                                     "You have used an item."	
#define	STR_INVALID_GUILD_NAME	     "Invalid guild name!"	
#define	STR_GUILD_FUND_NOT_ENOUGH	     "Guild fund has not reached %u silvers!"	
#define	STR_NOT_AUTHORIZED	                     "You have not been authorized!"	
#define	STR_ALLY_FULL	                                     "Allies List is full!"	
#define	STR_SYN_PLACE_FULL	        "All the posts have been occupied!"
#define	STR_WANTED_ORDER	        "%u silvers earnest money is deducted.  You have got No.%d Pursuing Order. Target: %s; Reward: %u silvers."
#define	STR_WANTED_INFO				"It is said that the wanted target appears around [%s]."
#define	STR_INVALID_WANTED	        "Invalid Pursuing Number！"
#define	STR_MAX_BONUTY				"You should offer a reward of %d silvers at most!"
#define	STR_MIN_BONUTY				"You should offer a reward of %d silvers at least!"
#define	STR_SUPERADD_BONUTY			"The reward for No.%d Pursuing Order is increased to %u silvers!"
#define	STR_LOWEST_SUPERADD_BONUTY	"You must increase %u silvers at lease!"
#define	STR_CANCEL_WANTED			"Pursuing Order for %u has been canceled."
#define	STR_NO_DISBAND	            "The guild is too big to be disbanded. Please transfer your guild power."	
#define	STR_PROTECTED_CODE	        "Please enter the protection code first."	
#define	STR_HIS_ALLY_FULL	        "The target's Alley List is full!"	
#define	STR_NOT_HERE	            "The player is not in the vicinity!"
#define	STR_NOT_ENOUGH_LEV			"You have not reached level %d!"
#define	STR_LEVEL_NOT_ENOUGH	    "The target's level is insufficient!"
#define	STR_INVALID_NAME	        "Invalid name."
#define	STR_INVALID_MSG	            "Invalid message!"
#define	STR_MAGIC_FAILED            "Magic failed!"
#define	STR_CANNOT_DEPOSIT	        "Error: The item is not suitable for deposit!"
#define	STR_FORBIDDEN_GUILD_NAME	"You are forbidden to use this guild name."
#define	STR_GUILD_INEXIST	        "The guild does not exist."
#define	STR_TEAM_EXPERIENCE	        "%d team experience points gained."
#define	STR_TEAM_EXPEX				"You gained  %d team experience points with additional rewarding experience points due to low level teammates."
#define	STR_LOST_EXPERIENCE	        "You lost %d experience points!"
#define	STR_KILLING_TO_MUCH	        "You have done too much killing. You will pay for what you have done."
#define	STR_NOT_PK_MODE	            "You can't attack the target in the current mode!"
#define	STR_NOT_PK_EXP	            "You cannot PK when your experience point is under 0."	

#define	STR_PK_FORBIDDEN	                     "PK is forbidden here."
#define	STR_MSG_SENT	   		     "Message sent successfully. The target will receive it as soon as he/she logs into the game."
#define	STR_MSG_FAILED				"Failed to leave message. Please leave message to a friend every %d minutes."
#define	STR_INVALID_COORDINATE	     "Invalid coordinates."
#define	STR_GONE	                                     "Gone"
#define	STR_JUMPED	                                     "Jumped"
#define	STR_CONNECTION_OFF	                     "Bad Connection. Log off automatically."
#define	STR_WEAPON_SKILL_UP	                     "Congratulations! Your weapon proficiency has been improved."
#define	STR_TEAMMATE_CANNOT_CREATE	     "[Team]You are already in a team and cannot create a new one."
#define	STR_CREATE_TEAM_FAILED	     "[Team]Failed to create a team."
#define	STR_FULLBAG_NO_MORE	                     "You bag is full and can't hold more items."
#define	STR_HEAVEY_BAG	                     "Your bag is so too heavy to hold any more items."
#define	STR_ITEM_NOT_FOUND	                     "The item is not found!"
#define	STR_ITEM_INEXIST	                     "The item does not exist!"
#define	STR_MONEYBAG_FULL	                     "Your moneybag is full!"
#define	STR_MAKE_ITEM_FAILED                      "Failed to generate map item [%u]."
#define	STR_MAKE_MONEY_FAILED	     "Failed to generate map money [%d]."
#define	STR_DAMAGED_REPAIR	                     "%s has been severely damaged. Please repair it soon; otherwise, it will be gone."
#define	STR_DURABILITY_REPAIR	                     "Durability of %s is too low. Please repair it soon to prevent further damaging."
#define	STR_FAR_CANNOT_PICK	                     "The item is too far away for you to pick up."
#define	STR_FULL_CANNOT_PICK	                     "Your bag is full and you can not pick up any more items."
#define	STR_PICK_MONEY	                     "You have picked up %u silvers."
#define	STR_FAILED_GENERATE_ITEM	     "Failed to generate the item."
#define	STR_OTHERS_ITEM	                     "You have to wait a little bit before you can pick up any items that were dropped from the monsters being killed by other players."
#define	STR_GOT_ITEM	                                     "You have got a(an) %s."
#define	STR_DRAGONBALL	                     "A [Dragon Ball] is required to improve equipment."
#define	STR_REPAIR_THEN_IMPROVE	     "Please repair the equipment before improving it."
#define	STR_SUPERIOR_ALREADY	                     "The equipment is already in superior grade."
#define	STR_CONNOT_IMPROVE	                     "The equipment cannot been improved."
#define	STR_METEOR	                                     "A [Meteor] is required to upgrade equipment."
#define	STR_REPAIR_THEN_UPGRADE	     "Please repair the equipment before upgrading it."
#define	STR_UPGRADE_NOMORE	                     "The equipment cannot be upgraded any more!"
#define	STR_MINE_WITH_PECKER   	     "You must use a pecker to mine."
#define	STR_NO_MINE	                                     "No mine here."
#define	STR_GOLD_ORE	                                     "You gained a gold ore!"
#define	STR_EUXENITE_ORE	                     "You gained an euxenite ore!"
#define	STR_IRON_ORE	                                     "You gained an iron ore!"
#define	STR_COPPER_ORE	                                     "You gained copper ore!"
#define	STR_SILVER_ORE	                     "You gained a silver ore!"
#define	STR_GAIN_GEM	                                     "Congratulations! You gained a gem!"
#define	STR_UNQUALIFIED	                     "Error: Failed to meet condition."
#define	STR_DIE	                                     "You are already dead."
#define	STR_DONOT_GIVE_UP	                     "You are taking on important responsibilities. How can you abandon yourself?"
#define	STR_CANNOT_JUMP	                     "You cannot jump!"
#define	STR_CHEAT	                                     "[Cheat]The points you are allotting are more than the limit."
#define	STR_FRIEND_LIST_FULL	                     "The target's friend list is full."
#define	STR_YOUR_FRIEND_ALREADY	    "The target has been your friend."
#define	STR_MAKE_FRIEND_SENT                     "Request of making friends has been sent out."
#define	STR_NOT_YOUR_FRIEND	                     "%s is not your friend."
#define	STR_NO_PK_VILLAGE	                     "PK is forbidden in Birth Village."
#define	STR_NEVER_PROPOSED	                     "%s never proposed to you."
#define	STR_SINGLE	                                     "You are still single."
#define	STR_NOT_YOUR_SPOUSE	                     "%s is not your spouse."
#define	STR_NOT_ENOUGH_MANA	                     "You don't have enough mana."
#define	STR_UNABLE_USE_ITEM	                     "Unable to use item!"
#define	STR_YOUR_BAG_FULL	                     "Your bag is full!"
#define	STR_INVALID_AMOUNT	                     "Invalid amount!"
#define	STR_REPAIR_FAILED	                     "Repair failed!"
#define	STR_INVALID_TITLE	                     "Error: Invalid title!"
#define	STR_NOT_FROM_YOUR_GUILD	     "The target does not belong to your guild."
#define	STR_ITEM_DAMAGED	                     "The item has been damaged!"
#define	STR_VITAL_POINT_STRICKEN	     "Your vital point has been stricken and you are unable to talk!"
#define	STR_CHANGE_NAME	                     "You have changed your name to %s."
#define	STR_INCREASE_MONEY	                     "[Your money is increased.]"
#define	STR_INCREASE_ITEM	                     "[Your item is increased.]"
#define	STR_KICKOUTALL	                     "Start kickoutall. All players are logging off and logging in is forbidden."
#define	STR_ACTION_SEEN	                     "ACTION can be seen."
#define	STR_ACTION_NOTSEEN	                     "ACTION cannot been seen."
#define	STR_NO_STOP	                                     "You cannot stop in the destination!"
#define	STR_LOCAL_TEST	                     "Caution: The command is for local test only. Otherwise the server may collapse!"
#define	STR_ACTION_UPDATED	                     "[ACTION has been updated.]"
#define	STR_KICK_OUT_GUILD	                     "%s has been kick out of the guild!"
#define	STR_NO_PRIZE	                                     "Sorry, no prize for you or the prize has not been verified in the prize claiming webpage."
#define	STR_NO_LV_BROADCAST	                     "Your level is not high enough and you cannot broadcast!"
#define	STR_NO_MANA_BROADCAST	     "Your mana is not high enough and you cannot broadcast!"
#define	STR_INVALID_CHARACTER	     "Invalid character is found in the message!"
#define	STR_LOW_LEVEL	                                     "Your level is too low!"
#define	STR_GM_NO_TEAM	                     "[GM] cannot use the team command."
#define	STR_INTEAM_NOJOIN	                     "[Team]You are already in a team and cannot join another team."
#define	STR_NO_APPLICANT     	                     "[Team]The applicant is not found."
#define	STR_NO_TEAM	                                     "[Team]The target has not created a team."
#define	STR_FORBIDDEN_JOIN	                                     "[Team]The team is forbidden access."
#define	STR_TEAM_FULL	                                     "[Team]The team is full."
#define	STR_NO_CAPTAIN_CLOSE	    "[Team]Please click on the captain."
#define	STR_JOIN_REQUEST_SENT	     "[Team]Request to join team has been sent out."
#define	STR_INVI_SENT	                                     "[Team]Invitation to join team has been sent out out. Please wait for response."
#define	STR_NO_TEAM_TO_INVITE	     "[Team]You haven't created a team. How can you accept other player to a team?"
#define	STR_NOT_CAPTAIN_INVITE	     "[Team]You are not the captain. How can you accept other player to the team?"
#define	STR_YOUR_TEAM_FULL		     "[Team]Your team is full."
#define	STR_APPLICANT_NOT_FOUND	     "[Team]The applicant is not found."
#define	STR_HAVE_JOIN_TEAM	                                     "[Team]You are already in a team and cannot join another team."
#define	STR_NOT_TO_JOIN	     "[Team]The target has not requested to join the team."
#define	STR_NOTEAM_TO_INVITE	                     "[Team]You haven't created a team and cannot invite others to join."
#define	STR_TEAM_CLOSED	                     "[Team]Team is closed. Please open it first."
#define	STR_NOT_CAPTAIN_ACCEPT	     "[Team]You are not the captain. How can you invite other players to the team?"
#define	STR_INVITED_NOT_FOUND	     "[Team]The invited target is not found."
#define	STR_HAS_IN_TEAM	                                     "[Team]The target is in another team. Invitation failed."
#define	STR_INVITE_SENT		"[Team]Invitation has been sent."
#define	STR_SENT_WAIT	                     "[Team]Request has been sent out. Please wait."
#define	STR_INTEAM_NOACCEPT       	                     "[Team]You have been in a team and cannot agree to join another team."
#define	STR_INVITER_NOT_FOUND	     "[Team]The inviter is not found."
#define	STR_NOT_CREATE_TEAM	                     "[Team]The target has not created a team."
#define	STR_HIS_TEAM_FULL	                     "[Team]The target's team is full."
#define	STR_NOT_BE_INVIITED	                     "[Team]The target did not invite you to the team."
#define	STR_NO_TEAM_TO_LEAVE                     "[Team]You are not in a team and cannot leave."
#define	STR_NO_TEAM_TO_DISMISS               "[Team]You haven't created a team yet and cannot dismiss."
#define	STR_NOT_CAPTAIN_DISMISS	                     "[Team]You are not the captain and cannot dismiss the team."
#define	STR_NO_TRADE_IN_BATTLE	     "Error: You cannot use trade command while in battle!"
#define	STR_NO_TRADE_IN_TEAM	     "Error: You cannot use trade command while you are in a team!"
#define	STR_NO_IN_TEAM		     "[Team]You do not have a team yet."
#define	STR_NO_TRADE_TARGET	                     "[Trade]The trading target is not found."
#define	STR_TARGET_TRADING	                     "[Trade]The target is trading with someone else. Please try later."
#define	STR_TRADING_REQEST_SENT	     "[Trade]Request for trading has been sent out."
#define	STR_NOT_FOR_TRADE	                     "Error: the item cannot be traded!"
#define	STR_FREE_PK	                                     "Free PK mode. You can attack anyone."
#define	STR_PEACE	                                     "Peace mode. You can only attack monsters and won't hurt other players."
#define	STR_TEAM_PK	                                     "Team PK mode. You can attack monsters and players except for your teammates."
#define	STR_JOIN_A_GUILD	                     "%s joined a guild."
#define	STR_BONUS					"Congratulations! You have got %u prizes.  Please go to trade market to claim prize!"
#define	STR_TO_MAKE_FRIEND			"%s wishes to make friends with you!"
#define	STR_MAKE_FRIEND				"%s and %s are friends from now on!"
#define	STR_BREAK_FRIEND			"%s broke up friendship with %s."
#define	STR_MARRY					"%s and %s are pronounced the husband and wife. They promise to love and care for each other for better or worse."
#define	STR_DIVORCE					"%s and %s got divorced because the love is not there anymore!"
#define	STR_SYN_CONQUER				"[%s] has occupied the Guild House finally after fighting bravely and persistently!"
#define	STR_POLICE_WANTED_ORDER		"Confirm：Target %s，this person was saw at %s recently."
#define	STR_GOTO_JAIL				"%s has killed too much and been put into the jail at last."

//---------------------------------------------------------------------------
#endif
