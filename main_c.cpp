
#include <iostream>

#define WIN32COMMON

#include <occi.h>

using namespace std;
using namespace oracle::occi;

Environment *G_ENV;
Connection *G_CON;
Statement *G_STATE;


bool connect();

int generateStatement();

void printResultSet(const std::string&);

void disConnect();

bool connect() {
    try {
        // 创建 OCCI 上下文环境  
        G_ENV = Environment::createEnvironment();
        if (nullptr == G_ENV) {
            printf("createEnvironment error.\n");
            return false;
        } else {
            cout << "createEnvironment success" << endl;
        }

        string name = "user_dev";
        string pass = "123456";
        string connectString = "127.0.0.1:1521/pdb";

        // 创建数据库连接  
        G_CON = G_ENV->createConnection(name, pass, connectString);
        if (nullptr == G_CON) {
            printf("createConnection error.\n");
            return false;
        } else {
            cout << "conn success" << endl;
        }
    }
    catch (SQLException e) {
        cout << e.what() << endl;
        return false;
    }
    
    return true;
}

int generateStatement() {
    
    try {
        G_STATE = G_CON->createStatement();
        if (NULL == G_STATE) {
            printf("createStatement error.\n");
            return -1;
        }
    }
    catch (SQLException e) {
        cout << e.what() << endl;
        return -1;
    }
    return 0;
}


void printResultSet(const std::string& sql) {
    try {
        ResultSet *pRs = G_STATE->executeQuery(sql);
        vector<MetaData> metaData = pRs->getColumnListMetaData();
        int count = metaData.size();
        for (const auto &item: metaData) {
            std::string cName = item.getString(oracle::occi::MetaData::ATTR_NAME);
            printf("%s,", cName.c_str());
        }
        printf("\n");
        while (pRs->next()) {
            for (int i = 0; i < count; ++i) {
                printf("%s,", pRs->getString(i + 1).c_str());
            }
            printf("\n");
        }
        G_STATE->closeResultSet(pRs);
    }
    catch (SQLException e) {
        cout << e.what() << endl;
    }
}


void disConnect() {
    // 终止 Statement 对象    
    if (G_STATE){
        G_CON->terminateStatement(G_STATE);
    }
    if (G_ENV){
        // 关闭连接  
        G_ENV->terminateConnection(G_CON);
        // 释放 OCCI 上下文环境    
        Environment::terminateEnvironment(G_ENV);
    }
    cout << "end!" << endl;
}


int main() {

    if (connect()){
        generateStatement();
       
        printResultSet("SELECT * FROM all_users");
        disConnect();
    }
    return 0;
}  