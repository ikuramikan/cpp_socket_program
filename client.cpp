#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 50000
#define BUFSIZE 4096

int main()
{
    int sockfd; // socket
    struct sockaddr_in server_address; // アドレスの指定に用いる構造体 IPv4
    int addr_len = sizeof(server_address);
    char buffer[BUFSIZE] = {0}; // バッファ
    char msg[BUFSIZE] = "";

    // socket (IPv4, TCP)
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        std::cerr << "socket failed" << std::endl;
        std::exit(EXIT_FAILURE);
    }
    
    // addressの設定
    server_address.sin_family = AF_INET; // IPv4を設定
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_address.sin_port = htons(PORT); // PORT番号を設定

    // connect
    if(connect(sockfd, (struct sockaddr *)&server_address, sizeof(server_address)) < 0)
    {
        std::cerr << "connect failed" << std::endl;
        std::exit(EXIT_FAILURE);
    }

    std::cout << "input your message: " ;
    std::cin >> msg ; // msg入力
    send(sockfd, msg, sizeof(msg), 0); // msgを送信
    
    recv(sockfd, buffer, sizeof(buffer), 0); // データを受信
    std::cout << buffer << std::endl; // 受信したデータを表示

    close(sockfd);

    return 0;
}