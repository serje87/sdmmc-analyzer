#include "SDMMCAnalyzerResults.h"
#include "SDMMCAnalyzer.h"
#include "SDMMCAnalyzerSettings.h"
#include "SDMMCHelpers.h"

SDMMCAnalyzerResults::SDMMCAnalyzerResults(SDMMCAnalyzer* analyzer, SDMMCAnalyzerSettings* settings)
:	AnalyzerResults(),
	mSettings(settings),
	mAnalyzer(analyzer)
{
}

SDMMCAnalyzerResults::~SDMMCAnalyzerResults()
{
}

static const char* cmd_abbrev_from_number(unsigned int cmd_number)
{
	switch (cmd_number) {
	case 0: return "GO_IDLE_STATE";
	case 1: return "RESERVED";
	case 2: return "ALL_SEND_CID";
	case 3: return "SEND_RELATIVE_ADDR";
	case 4: return "SET_DSR";
	case 5: return "RESERVED FOR SDIO";
	case 6: return "SWITCH";
	case 7: return "SELECT/DESELECT_CARD";
	case 8: return "SEND_IF_COND";
	case 9: return "SEND_CSD";
	case 10: return "SEND_CID";
	case 11: return "VOLTAGE_SWITCH";
	case 12: return "STOP_TRANSMISSION";
	case 13: return "SEND_STATUS";
	case 14: return "RESERVED";
	case 15: return "GO_INACTIVE_STATE";
	case 16: return "SET_BLOCKLEN";
	case 17: return "READ_SINGLE_BLOCK";
	case 18: return "READ_MULTIPLE_BLOCK";
	case 19: return "SEND_TUNING_BLOCK";
	case 20: return "SPEED_CLASS_CONTROL";
	case 21: return "RESERVED";
	case 22: return "ADDRESS_EXTENSION";
	case 23: return "SET_BLOCK_COUNT";
	case 24: return "WRITE_BLOCK";
	case 25: return "WRITE_MULTIPLE_BLOCK";
	case 26: return "RESERVED";
	case 27: return "PROGRAM_CSD";
	case 28: return "SET_WRITE_PROT";
	case 29: return "CLR_WRITE_PROT";
	case 30: return "SEND_WRITE_PROT";
	case 31: return "RESERVED";
	case 32: return "ERASE_WR_BLK_START";
	case 33: return "ERASE_WR_BLK_END";
	case 34: return "RESERVED";
	case 35: return "RESERVED";
	case 36: return "RESERVED";
	case 37: return "RESERVED";
	case 38: return "ERASE";
	case 39: return "RESERVED";
	case 40: return "DEFINED_BY_DPS_SPEC";
	case 41: return "RESERVED";
	case 42: return "LOCK_UNLOCK";
	case 43: return "RESERVED";
	case 44: return "RESERVED";
	case 45: return "RESERVED";
	case 46: return "RESERVED";
	case 47: return "RESERVED";
	case 48: return "RESERVED";
	case 49: return "RESERVED";
	case 50: return "RESERVED";
	case 51: return "SEND_SCR";
	case 52: return "COMMAND_FOR_SDIO";
	case 53: return "COMMAND_FOR_SDIO";
	case 54: return "COMMAND_FOR_SDIO";
	case 55: return "APP_CMD";
	case 56: return "GEN_CMD";
	case 57: return "RESERVED";
	case 58: return "READ_OCR";
	case 59: return "RESERVED";
	case 60: return "RESERVED";
	case 61: return "RESERVED";
	case 62: return "RESERVED";
	case 63: return "RESERVED";
	default: return "INVALID";
	}
}

static const char* acmd_abbrev_from_number(unsigned int acmd_number)
{
	switch (acmd_number) {
	case 0: return "RESERVED";
	case 1: return "RESERVED";
	case 2: return "RESERVED";
	case 3: return "RESERVED";
	case 4: return "RESERVED";
	case 5: return "RESERVED";
	case 6: return "SET_BUS_WIDTH";
	case 7: return "RESERVED";
	case 8: return "RESERVED";
	case 9: return "RESERVED";
	case 10: return "RESERVED";
	case 11: return "RESERVED";
	case 12: return "RESERVED";
	case 13: return "SD_STATUS";
	case 14: return "RESERVED_FOR_DPS_SPEC";
	case 15: return "RESERVED_FOR_DPS_SPEC";
	case 16: return "RESERVED_FOR_DPS_SPEC";
	case 17: return "RESERVED";
	case 18: return "RESERVED_FOR_SD_SECURITY";
	case 19: return "RESERVED";
	case 20: return "RESERVED";
	case 21: return "RESERVED";
	case 22: return "SEND_NUM_WR_BLOCKS";
	case 23: return "SET_WR_BLK_ERASE_COUNT";
	case 24: return "RESERVED";
	case 25: return "RESERVED_FOR_SD_SECURITY";
	case 26: return "RESERVED_FOR_SD_SECURITY";
	case 27: return "SHALL_NOT_USE";
	case 28: return "RESERVED_FOR_DPS_SPEC";
	case 29: return "RESERVED";
	case 30: return "RESERVED_FOR_SECURITY_SPEC";
	case 31: return "RESERVED_FOR_SECURITY_SPEC";
	case 32: return "RESERVED_FOR_SECURITY_SPEC";
	case 33: return "RESERVED_FOR_SECURITY_SPEC";
	case 34: return "RESERVED_FOR_SECURITY_SPEC";
	case 35: return "RESERVED_FOR_SECURITY_SPEC";
	case 36: return "RESERVED";
	case 37: return "RESERVED";
	case 38: return "RESERVED_FOR_SD_SECURITY";
	case 39: return "RESERVED";
	case 40: return "RESERVED";
	case 41: return "SD_SEND_OP_COND";
	case 42: return "SET_CLR_CARD_DETECT";
	case 43: return "RESERVED_FOR_SD_SECURITY";
	case 44: return "RESERVED_FOR_SD_SECURITY";
	case 45: return "RESERVED_FOR_SD_SECURITY";
	case 46: return "RESERVED_FOR_SD_SECURITY";
	case 47: return "RESERVED_FOR_SD_SECURITY";
	case 48: return "RESERVED_FOR_SD_SECURITY";
	case 49: return "RESERVED_FOR_SD_SECURITY";
	case 50: return "RESERVED";
	case 51: return "SEND_SCR";
	case 52: return "RESERVED";
	case 53: return "RESERVED";
	case 54: return "RESERVED";
	case 55: return "NOT_EXIST";
	case 56: return "RESERVED_FOR_SECURITY_SPEC";
	case 57: return "RESERVED_FOR_SECURITY_SPEC";
	case 58: return "RESERVED_FOR_SECURITY_SPEC";
	case 59: return "RESERVED_FOR_SECURITY_SPEC";
	case 60: return "RESERVED";
	case 61: return "RESERVED";
	case 62: return "RESERVED";
	case 63: return "RESERVED";
	default: return "INVALID";
	}
}

void SDMMCAnalyzerResults::GenerateBubbleText(U64 frame_index, Channel& channel, DisplayBase display_base)
{
	ClearResultStrings();
	Frame frame = GetFrame(frame_index);

	switch (frame.mType) {
	case FRAMETYPE_HEADER:
		if (frame.mData1 == 1)
			AddResultString("Host sending");
		else
			AddResultString("Card sending");
		break;

	case FRAMETYPE_COMMAND:
	{
		char str_cmd[4];
		char str_arg[33];

		AnalyzerHelpers::GetNumberString(frame.mData1, Decimal, 6, str_cmd, sizeof(str_cmd));
		AnalyzerHelpers::GetNumberString(frame.mData2, display_base, 32, str_arg, sizeof(str_arg));

		AddResultString("CMD", str_cmd);
		AddResultString("CMD", str_cmd, ", arg=", str_arg, ", abbr=", cmd_abbrev_from_number(frame.mData1));
		break;
	}

    case FRAMETYPE_ACOMMAND:
    {
        char str_cmd[4];
        char str_arg[33];

        AnalyzerHelpers::GetNumberString(frame.mData1, Decimal, 6, str_cmd, sizeof(str_cmd));
        AnalyzerHelpers::GetNumberString(frame.mData2, display_base, 32, str_arg, sizeof(str_arg));

        AddResultString("ACMD", str_cmd);
		AddResultString("ACMD", str_cmd, ", arg=", str_arg, ", abbr=", acmd_abbrev_from_number(frame.mData1));
        break;
    }

	case FRAMETYPE_RESPONSE:
	{
		char str_32[33];

		switch (frame.mFlags) {
		case MMC_RSP_R1:
		{
			const char *str_state = "reserved";
			std::string str_flags("");

			switch ((frame.mData1 >> 9) & 0xf) {
			case 0: str_state = "Idle"; break;
			case 1: str_state = "Ready"; break;
			case 2: str_state = "Ident"; break;
			case 3: str_state = "Stby"; break;
			case 4: str_state = "Tran"; break;
			case 5: str_state = "Data"; break;
			case 6: str_state = "Rcv"; break;
			case 7: str_state = "Prg"; break;
			case 8: str_state = "Dis"; break;
			case 9: str_state = "Btst"; break;
			case 10: str_state = "Slp "; break;
			}

			AnalyzerHelpers::GetNumberString(frame.mData1, display_base, 32, str_32, sizeof(str_32));
			
			AddResultString("R1");
			AddResultString("R1, ", str_state);
			AddResultString("R1, ", str_state, ", rsp=", str_32);

			if (frame.mData1 & (1 << 31))
					str_flags += " ADDRESS_OUT_OF_RANGE";
			if (frame.mData1 & (1 << 30))
					str_flags += " ADDRESS_MISALIGN";
			if (frame.mData1 & (1 << 29))
					str_flags += " BLOCK_LEN_ERROR";
			if (frame.mData1 & (1 << 28))
					str_flags += " ERASE_SEQ_ERROR";
			if (frame.mData1 & (1 << 27))
					str_flags += " ERASE_PARAM";
			if (frame.mData1 & (1 << 26))
					str_flags += " WP_VIOLATION";
			if (frame.mData1 & (1 << 25))
					str_flags += " CARD_IS_LOCKED";
			if (frame.mData1 & (1 << 24))
					str_flags += " LOCK_UNLOCK_FAILED";
			if (frame.mData1 & (1 << 23))
					str_flags += " COM_CRC_ERROR";
			if (frame.mData1 & (1 << 22))
					str_flags += " ILLEGAL_COMMAND";
			if (frame.mData1 & (1 << 21))
					str_flags += " CARD_ECC_FAILED";
			if (frame.mData1 & (1 << 20))
					str_flags += " CC_ERROR";
			if (frame.mData1 & (1 << 19))
					str_flags += " ERROR";
			if (frame.mData1 & (1 << 18))
					str_flags += " UNDERRUN";
			if (frame.mData1 & (1 << 17))
					str_flags += " OVERRUN";
			if (frame.mData1 & (1 << 16))
					str_flags += " CID/CSD_OVERWRITE";
			if (frame.mData1 & (1 << 15))
					str_flags += " WP_ERASE_SKIP";
			if (frame.mData1 & (1 << 13))
					str_flags += " ERASE_RESET";
			if (frame.mData1 & (1 << 8))
					str_flags += " READY_FOR_DATA";
			if (frame.mData1 & (1 << 7))
					str_flags += " SWITCH_ERROR";
			if (frame.mData1 & (1 << 5))
					str_flags += " APP_CMD";

			if (str_flags.length() > 0)
				AddResultString("R1, ", str_state, ", rsp=", str_32, str_flags.c_str());

			break;
		}
		case MMC_RSP_R2_CID:
		{
			std::string res("R2");
			char pname[7], prv_str[4], psn_str[12];
			char rsp_str[64];

			AddResultString(res.c_str());

			res += " [CID]";
			AddResultString(res.c_str());

			res += " rsp=";
			AnalyzerHelpers::GetNumberString(frame.mData1 >> 32, display_base, 32, rsp_str, sizeof(rsp_str));
			res += rsp_str;
			res += " ";
			AnalyzerHelpers::GetNumberString(frame.mData1 & 0xffffffffull, display_base, 32, rsp_str, sizeof(rsp_str));
			res += rsp_str;
			res += " ";
			AnalyzerHelpers::GetNumberString(frame.mData2 >> 32, display_base, 32, rsp_str, sizeof(rsp_str));
			res += rsp_str;
			res += " ";
			AnalyzerHelpers::GetNumberString(frame.mData2 & 0xffffffffull, display_base, 32, rsp_str, sizeof(rsp_str));
			res += rsp_str;
			AddResultString(res.c_str());

			pname[0] = (frame.mData1 >> 32) & 0xff;
			pname[1] = (frame.mData1 >> 24) & 0xff;
			pname[2] = (frame.mData1 >> 16) & 0xff;
			pname[3] = (frame.mData1 >>  8) & 0xff;
			pname[4] = (frame.mData1 >>  0) & 0xff;
			pname[5] = (frame.mData2 >> 56) & 0xff;
			pname[6] = 0;

			unsigned prv = (unsigned)((frame.mData2 >> 48) & 0xff);
			prv_str[0] = '0' + ((prv >> 4) & 0x0f);
			prv_str[1] = '.';
			prv_str[2] = '0' + (prv & 0x0f);
			prv_str[3] = 0;

			unsigned psn = (unsigned)((frame.mData2 >> 16) & 0xfffffffful);
			AnalyzerHelpers::GetNumberString(psn, Decimal, 32, psn_str, sizeof(psn_str));

			res += " pnm='";
			res += pname;
			res += "' prv=";
			res += prv_str;
			res += " psn=";
			res += psn_str;
			AddResultString(res.c_str());

			break;
		}
		case MMC_RSP_R2_CSD:
		{
			std::string res("R2");
			char rsp_str[64];

			AddResultString(res.c_str());

			res += " [CSD]";
			AddResultString(res.c_str());

			res += " rsp=";
			AnalyzerHelpers::GetNumberString(frame.mData1 >> 32, display_base, 32, rsp_str, sizeof(rsp_str));
			res += rsp_str;
			res += " ";
			AnalyzerHelpers::GetNumberString(frame.mData1 & 0xffffffffull, display_base, 32, rsp_str, sizeof(rsp_str));
			res += rsp_str;
			res += " ";
			AnalyzerHelpers::GetNumberString(frame.mData2 >> 32, display_base, 32, rsp_str, sizeof(rsp_str));
			res += rsp_str;
			res += " ";
			AnalyzerHelpers::GetNumberString(frame.mData2 & 0xffffffffull, display_base, 32, rsp_str, sizeof(rsp_str));
			res += rsp_str;
			AddResultString(res.c_str());

			break;
		}
		case MMC_RSP_R3:
			AnalyzerHelpers::GetNumberString(frame.mData1, Hexadecimal, 32, str_32, sizeof(str_32));
			AddResultString("R3");
			AddResultString("R3, ocr=", str_32);
			break;
		case MMC_RSP_R4:
			AddResultString("R4");
			break;
		case MMC_RSP_R5:
			AddResultString("R5");
			break;
		}
		break;
	}

	case FRAMETYPE_CRC:
	{
		char str_crc[8];

		AnalyzerHelpers::GetNumberString(frame.mData1, Hexadecimal, 7, str_crc, sizeof(str_crc));

		AddResultString("CRC");
		AddResultString("CRC=", str_crc);
		break;
	}

	default:
		AddResultString("error");
	}
}

void SDMMCAnalyzerResults::GenerateExportFile(const char* file, DisplayBase display_base, U32 export_type_user_id)
{
	ClearResultStrings();
	AddResultString("not supported");
}

void SDMMCAnalyzerResults::GenerateFrameTabularText(U64 frame_index, DisplayBase display_base)
{
	ClearTabularText();
	Frame frame = GetFrame(frame_index);

	switch (frame.mType) {
	case FRAMETYPE_HEADER:
		if (frame.mData1 == 1)
			AddTabularText("Host sending");
		else
			AddTabularText("Card sending");
		break;

	case FRAMETYPE_COMMAND:
	{
		char str_cmd[4];
		char str_arg[33];

		AnalyzerHelpers::GetNumberString(frame.mData1, Decimal, 6, str_cmd, sizeof(str_cmd));
		AnalyzerHelpers::GetNumberString(frame.mData2, display_base, 32, str_arg, sizeof(str_arg));

		AddTabularText("CMD", str_cmd, ", arg=", str_arg, ", abbr=", cmd_abbrev_from_number(frame.mData1));
		break;
	}

	case FRAMETYPE_ACOMMAND:
	{
		char str_cmd[4];
		char str_arg[33];

		AnalyzerHelpers::GetNumberString(frame.mData1, Decimal, 6, str_cmd, sizeof(str_cmd));
		AnalyzerHelpers::GetNumberString(frame.mData2, display_base, 32, str_arg, sizeof(str_arg));

		AddTabularText("ACMD", str_cmd, ", arg=", str_arg, ", abbr=", acmd_abbrev_from_number(frame.mData1));
		break;
	}

	case FRAMETYPE_RESPONSE:
	{
		char str_32[33];

		switch (frame.mFlags) {
		case MMC_RSP_R1:
		{
			const char* str_state = "reserved";
			std::string str_flags("");

			switch ((frame.mData1 >> 9) & 0xf) {
			case 0: str_state = "Idle"; break;
			case 1: str_state = "Ready"; break;
			case 2: str_state = "Ident"; break;
			case 3: str_state = "Stby"; break;
			case 4: str_state = "Tran"; break;
			case 5: str_state = "Data"; break;
			case 6: str_state = "Rcv"; break;
			case 7: str_state = "Prg"; break;
			case 8: str_state = "Dis"; break;
			case 9: str_state = "Btst"; break;
			case 10: str_state = "Slp "; break;
			}

			AnalyzerHelpers::GetNumberString(frame.mData1, display_base, 32, str_32, sizeof(str_32));

			// AddTabularText("R1, ", str_state, ", rsp=", str_32);

			if (frame.mData1 & (1 << 31))
				str_flags += " ADDRESS_OUT_OF_RANGE";
			if (frame.mData1 & (1 << 30))
				str_flags += " ADDRESS_MISALIGN";
			if (frame.mData1 & (1 << 29))
				str_flags += " BLOCK_LEN_ERROR";
			if (frame.mData1 & (1 << 28))
				str_flags += " ERASE_SEQ_ERROR";
			if (frame.mData1 & (1 << 27))
				str_flags += " ERASE_PARAM";
			if (frame.mData1 & (1 << 26))
				str_flags += " WP_VIOLATION";
			if (frame.mData1 & (1 << 25))
				str_flags += " CARD_IS_LOCKED";
			if (frame.mData1 & (1 << 24))
				str_flags += " LOCK_UNLOCK_FAILED";
			if (frame.mData1 & (1 << 23))
				str_flags += " COM_CRC_ERROR";
			if (frame.mData1 & (1 << 22))
				str_flags += " ILLEGAL_COMMAND";
			if (frame.mData1 & (1 << 21))
				str_flags += " CARD_ECC_FAILED";
			if (frame.mData1 & (1 << 20))
				str_flags += " CC_ERROR";
			if (frame.mData1 & (1 << 19))
				str_flags += " ERROR";
			if (frame.mData1 & (1 << 18))
				str_flags += " UNDERRUN";
			if (frame.mData1 & (1 << 17))
				str_flags += " OVERRUN";
			if (frame.mData1 & (1 << 16))
				str_flags += " CID/CSD_OVERWRITE";
			if (frame.mData1 & (1 << 15))
				str_flags += " WP_ERASE_SKIP";
			if (frame.mData1 & (1 << 13))
				str_flags += " ERASE_RESET";
			if (frame.mData1 & (1 << 8))
				str_flags += " READY_FOR_DATA";
			if (frame.mData1 & (1 << 7))
				str_flags += " SWITCH_ERROR";
			if (frame.mData1 & (1 << 5))
				str_flags += " APP_CMD";

			if (str_flags.length() > 0)
				AddTabularText("R1, ", str_state, ", rsp=", str_32, str_flags.c_str());

			break;
		}
		case MMC_RSP_R2_CID:
		{
			std::string res("R2");
			char pname[7], prv_str[4], psn_str[12];
			char rsp_str[64];

			// AddTabularText(res.c_str());

			res += " [CID]";
			// AddTabularText(res.c_str());

			res += " rsp=";
			AnalyzerHelpers::GetNumberString(frame.mData1 >> 32, display_base, 32, rsp_str, sizeof(rsp_str));
			res += rsp_str;
			res += " ";
			AnalyzerHelpers::GetNumberString(frame.mData1 & 0xffffffffull, display_base, 32, rsp_str, sizeof(rsp_str));
			res += rsp_str;
			res += " ";
			AnalyzerHelpers::GetNumberString(frame.mData2 >> 32, display_base, 32, rsp_str, sizeof(rsp_str));
			res += rsp_str;
			res += " ";
			AnalyzerHelpers::GetNumberString(frame.mData2 & 0xffffffffull, display_base, 32, rsp_str, sizeof(rsp_str));
			res += rsp_str;
			// AddTabularText(res.c_str());

			pname[0] = (frame.mData1 >> 32) & 0xff;
			pname[1] = (frame.mData1 >> 24) & 0xff;
			pname[2] = (frame.mData1 >> 16) & 0xff;
			pname[3] = (frame.mData1 >> 8) & 0xff;
			pname[4] = (frame.mData1 >> 0) & 0xff;
			pname[5] = (frame.mData2 >> 56) & 0xff;
			pname[6] = 0;

			unsigned prv = (unsigned)((frame.mData2 >> 48) & 0xff);
			prv_str[0] = '0' + ((prv >> 4) & 0x0f);
			prv_str[1] = '.';
			prv_str[2] = '0' + (prv & 0x0f);
			prv_str[3] = 0;

			unsigned psn = (unsigned)((frame.mData2 >> 16) & 0xfffffffful);
			AnalyzerHelpers::GetNumberString(psn, Decimal, 32, psn_str, sizeof(psn_str));

			res += " pnm='";
			res += pname;
			res += "' prv=";
			res += prv_str;
			res += " psn=";
			res += psn_str;
			AddTabularText(res.c_str());

			break;
		}
		case MMC_RSP_R2_CSD:
		{
			std::string res("R2");
			char rsp_str[64];

			// AddTabularText(res.c_str());

			res += " [CSD]";
			// AddTabularText(res.c_str());

			res += " rsp=";
			AnalyzerHelpers::GetNumberString(frame.mData1 >> 32, display_base, 32, rsp_str, sizeof(rsp_str));
			res += rsp_str;
			res += " ";
			AnalyzerHelpers::GetNumberString(frame.mData1 & 0xffffffffull, display_base, 32, rsp_str, sizeof(rsp_str));
			res += rsp_str;
			res += " ";
			AnalyzerHelpers::GetNumberString(frame.mData2 >> 32, display_base, 32, rsp_str, sizeof(rsp_str));
			res += rsp_str;
			res += " ";
			AnalyzerHelpers::GetNumberString(frame.mData2 & 0xffffffffull, display_base, 32, rsp_str, sizeof(rsp_str));
			res += rsp_str;
			AddTabularText(res.c_str());

			break;
		}
		case MMC_RSP_R3:
			AnalyzerHelpers::GetNumberString(frame.mData1, Hexadecimal, 32, str_32, sizeof(str_32));
			AddTabularText("R3, ocr=", str_32);
			break;
		case MMC_RSP_R4:
			AddTabularText("R4");
			break;
		case MMC_RSP_R5:
			AddTabularText("R5");
			break;
		}
		break;
	}

	case FRAMETYPE_CRC:
	{
		char str_crc[8];

		AnalyzerHelpers::GetNumberString(frame.mData1, Hexadecimal, 7, str_crc, sizeof(str_crc));

		AddTabularText("CRC=", str_crc);
		break;
	}

	default:
		AddTabularText("error");
	}
}

void SDMMCAnalyzerResults::GeneratePacketTabularText(U64 packet_id, DisplayBase display_base)
{
	ClearResultStrings();
	AddResultString("not supported");
}

void SDMMCAnalyzerResults::GenerateTransactionTabularText(U64 transaction_id, DisplayBase display_base)
{
	ClearResultStrings();
	AddResultString("not supported");
}
