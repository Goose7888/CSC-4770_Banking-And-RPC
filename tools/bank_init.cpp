/* bank-init.cpp */

#include "bank_init.h"

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " [--bank1] [--bank2]" << std::endl;
        return 1;
    }

    std::string argument = argv[1];
    int operation_mode;
    if (argument == "--bank1") {
        operation_mode = BANK1;
    }
    else if (argument == "--bank2") {
        operation_mode = BANK2;
    }
    else {
        std::cerr << "Usage: " << argv[0] << " [--bank1] [--bank2]" << std::endl;
        return 1;
    }

    sqlite3* db = initServer(operation_mode);
    if (db == nullptr) {
        sqlite3_close(db);
        return 1;
    }

    // Creates Accounts table
    initDB(db);

    // fill table
    fillAccounts(db, operation_mode);

    sqlite3_close(db);
    return 0;
}

sqlite3* initServer(int operation_mode) {
    std::string dbPath = "";
    if (operation_mode == BANK1) {
        dbPath = "bank1.db";
    }
    else if (operation_mode == BANK2) {
        dbPath = "bank2.db";
    }
    else {
        std::cerr << "Invalid operation mode!";
        return nullptr;
    }

    sqlite3* db;
    if (sqlite3_open(dbPath.c_str(), &db) != SQLITE_OK) {
        std::cerr << "Cannot open " << dbPath << std::endl;
        return nullptr;
    }
    return db;
}

void initDB(sqlite3* db) {

    int result = 0;
    std::string zStmt = "SELECT * FROM sqlite_master WHERE type=\'table\' AND name=\'Accounts\';";

    sqlite3_stmt* ppStmt = nullptr;
    const char* pzTail = nullptr;
    if (sqlite3_prepare_v2(db, zStmt.c_str(), zStmt.length(), &ppStmt, &pzTail) != SQLITE_OK) {
        std::cerr << "Cannot prepare statement!" << std::endl;
        return;
    }

    // If no results, Accounts table needs to be created
    if (sqlite3_step(ppStmt) == SQLITE_DONE) {
        zStmt = "CREATE TABLE Accounts (ID TEXT PRIMARY KEY, Balance INT NOT NULL)";
        sqlite3_stmt* ctblStmt = nullptr;
        if (sqlite3_prepare_v2(db, zStmt.c_str(), zStmt.length(), &ctblStmt, &pzTail) != SQLITE_OK) {
            std::cerr << "Cannot prepare statement!" << std::endl;
            return;
        }

        result = sqlite3_step(ctblStmt);

        if (result != SQLITE_DONE) {
            std::cerr << "Cannot create Accounts table!" << std::endl;
        }

        sqlite3_finalize(ctblStmt);
    }

    // At this point, the Accounts table now exists 🎉🎉
    sqlite3_finalize(ppStmt);
}

void insertRecord(sqlite3* db, std::string acct_name, unsigned int balance) {
    char buildSql[128] = "";
    const char* zSql = buildSql;
    sqlite3_stmt* ppStmt = nullptr;
    const char* pzTail = nullptr;
    int result = 0;

    sprintf(buildSql, "INSERT INTO Accounts (ID, Balance) VALUES (\'%s\', %u)", acct_name.c_str(), balance);

    result = sqlite3_prepare_v2(db, zSql, strlen(zSql), &ppStmt, &pzTail);

    if (result != SQLITE_OK) {
        std::cerr << "Unable to prepare statement!" << std::endl;
        std::cerr << "Status: " << result << std::endl;
        return;
    }

    result = sqlite3_step(ppStmt);

    if (result != SQLITE_DONE) {
        std::cerr << "Error inserting record " << acct_name << "!" << std::endl;
    }

    sqlite3_finalize(ppStmt);
}

void fillAccounts(sqlite3* db, int operationMode) {
    if (operationMode == BANK1) {
        insertRecord(db, "b1_30S70T3A", 268);
        insertRecord(db, "b1_YYPGZENX", 990);
        insertRecord(db, "b1_KWMP7ZXT", 435);
        insertRecord(db, "b1_53JYFJHP", 491);
        insertRecord(db, "b1_R1GHOURB", 206);
        insertRecord(db, "b1_MZDQMF17", 300);
        insertRecord(db, "b1_86AZV0LU", 433);
        insertRecord(db, "b1_T4793KVQ", 638);
        insertRecord(db, "b1_F24I25EM", 551);
        insertRecord(db, "b1_091RAPP8", 747);
        insertRecord(db, "b1_V7Y0I184", 477);
        insertRecord(db, "b1_HFUARLIR", 788);
        insertRecord(db, "b1_2DRJP62N", 764);
        insertRecord(db, "b1_OAOSYQCJ", 694);
        insertRecord(db, "b1_JIL16BW5", 778);
        insertRecord(db, "b1_4GIKEW61", 984);
        insertRecord(db, "b1_QDFTDGQN", 640);
        insertRecord(db, "b1_CL23LR0J", 677);
        insertRecord(db, "b1_XJZCUCKF", 16);
        insertRecord(db, "b1_SHWLSXU2", 873);
        insertRecord(db, "b1_EOTU1HEY", 858);
        insertRecord(db, "b1_ZMQ392OK", 436);
        insertRecord(db, "b1_LKNDHMYG", 476);
        insertRecord(db, "b1_GRKMGXI3", 821);
        insertRecord(db, "b1_1PHVOISZ", 379);
        insertRecord(db, "b1_NNEEX3BV", 636);
        insertRecord(db, "b1_8UBNWNMH", 473);
        insertRecord(db, "b1_US8W485D", 572);
        insertRecord(db, "b1_PQ56CTF0", 754);
        insertRecord(db, "b1_BX2FKDZW", 193);
        insertRecord(db, "b1_WVYOJO9S", 384);
        insertRecord(db, "b1_ITVXS9TE", 139);
        insertRecord(db, "b1_SDU6F650", 514);
        insertRecord(db, "b1_DBRFNROW", 978);
        insertRecord(db, "b1_89OPVCYJ", 861);
        insertRecord(db, "b1_UGLY4WIF", 360);
        insertRecord(db, "b1_FEI727SB", 652);
        insertRecord(db, "b1_1CEGBSCX", 600);
        insertRecord(db, "b1_MJBQJDMT", 425);
        insertRecord(db, "b1_HH8ZIX6G", 604);
        insertRecord(db, "b1_3F58QIGC", 173);
        insertRecord(db, "b1_OM2HY208", 386);
        insertRecord(db, "b1_AKZ07DAU", 817);
        insertRecord(db, "b1_5IW95YKQ", 920);
        insertRecord(db, "b1_RPTJEJ4D", 330);
        insertRecord(db, "b1_CNQSM3E9", 99);
        insertRecord(db, "b1_YLN1LOY5", 21);
        insertRecord(db, "b1_JTKAT98R", 741);
        insertRecord(db, "b1_EQHJ1KRN", 136);
        insertRecord(db, "b1_0YETA42A", 215);
        insertRecord(db, "b1_LWA28PL6", 181);
        insertRecord(db, "b1_7T7BH9V2", 8);
        insertRecord(db, "b1_214KPUFO", 986);
        insertRecord(db, "b1_OZ13XFPK", 992);
        insertRecord(db, "b1_9XYCWZ97", 617);
        insertRecord(db, "b1_V4MM4AJ3", 351);
        insertRecord(db, "b1_G2IVDV3Z", 967);
        insertRecord(db, "b1_B0F4CGDL", 285);
        insertRecord(db, "b1_X7CDK0XH", 156);
        insertRecord(db, "b1_I59NSL73", 650);
    }
    else if (operationMode == BANK2) {
        insertRecord(db, "b2_NKDRKENU", 381);
        insertRecord(db, "b2_JI90JY7H", 405);
        insertRecord(db, "b2_4G69RJHD", 854);
        insertRecord(db, "b2_QO3IZ419", 747);
        insertRecord(db, "b2_BL018FBV", 598);
        insertRecord(db, "b2_6JXA6ZLR", 954);
        insertRecord(db, "b2_SRUKFK5E", 70);
        insertRecord(db, "b2_DORTN4FA", 924);
        insertRecord(db, "b2_ZMO2MPZ6", 678);
        insertRecord(db, "b2_KULBUA9S", 952);
        insertRecord(db, "b2_FRIL3LTO", 541);
        insertRecord(db, "b2_1ZFUB53B", 661);
        insertRecord(db, "b2_NXC3AQM7", 569);
        insertRecord(db, "b2_8V9CIBW3", 673);
        insertRecord(db, "b2_325LQVGP", 294);
        insertRecord(db, "b2_P024ZGQL", 638);
        insertRecord(db, "b2_AYZEX0A8", 607);
        insertRecord(db, "b2_W5NN6BK4", 689);
        insertRecord(db, "b2_H3KWEW40", 755);
        insertRecord(db, "b2_C1G5DHEM", 208);
        insertRecord(db, "b2_Y8DEL1YI", 392);
        insertRecord(db, "b2_J6AOTM85", 703);
        insertRecord(db, "b2_547X27I1", 668);
        insertRecord(db, "b2_0B460I2N", 942);
        insertRecord(db, "b2_M91F92CJ", 84);
        insertRecord(db, "b2_77YYHNWF", 29);
        insertRecord(db, "b2_TEV7G861", 862);
        insertRecord(db, "b2_ECSHOSPY", 498);
        insertRecord(db, "b2_9APQWD0K", 814);
        insertRecord(db, "b2_VHMZ5XJG", 977);
        insertRecord(db, "b2_GFJ838TC", 260);
        insertRecord(db, "b2_2DGICTDY", 912);
        insertRecord(db, "b2_OOFFY4CW", 522);
        insertRecord(db, "b2_AVCOXONI", 194);
        insertRecord(db, "b2_VT9X596E", 548);
        insertRecord(db, "b2_QR67DUG1", 190);
        insertRecord(db, "b2_CY3GME0X", 56);
        insertRecord(db, "b2_XW0PKPAT", 741);
        insertRecord(db, "b2_JUWYTAUF", 602);
        insertRecord(db, "b2_41T81V4B", 173);
        insertRecord(db, "b2_ZZQH0FOY", 433);
        insertRecord(db, "b2_LXNQ80YU", 518);
        insertRecord(db, "b2_64KZGKIQ", 342);
        insertRecord(db, "b2_S2HIPVSC", 203);
        insertRecord(db, "b2_N0ERNG28", 733);
        insertRecord(db, "b2_97B1W1MV", 99);
        insertRecord(db, "b2_U58A4LWR", 836);
        insertRecord(db, "b2_G35J36GN", 561);
        insertRecord(db, "b2_1B2SBRQ9", 832);
        insertRecord(db, "b2_W8Z1J295", 957);
        insertRecord(db, "b2_IGWBSMKS", 363);
        insertRecord(db, "b2_3ESKQ73O", 41);
        insertRecord(db, "b2_PBPTZRDK", 679);
        insertRecord(db, "b2_KJM27CX6", 18);
        insertRecord(db, "b2_6HJLFX72", 992);
        insertRecord(db, "b2_RFGUEHRP", 261);
        insertRecord(db, "b2_DM44MS1L", 419);
        insertRecord(db, "b2_YK0DVDLH", 298);
        insertRecord(db, "b2_TIXMUYV3", 750);
        insertRecord(db, "b2_FPUV2IFZ", 860);
    }
}
