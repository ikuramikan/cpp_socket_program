#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 50000
#define BUFSIZE 4096

int main()
{
    int serverfd; // server用socket
    int clientfd; // client用socket（通信相手）
    struct sockaddr_in address; // アドレスの指定に用いる構造体 IPv4
    int addr_len = sizeof(address);
    char buffer[BUFSIZE] = {0}; // バッファ
    char msg[BUFSIZE] = "Thank you for your message!";

    // socket (IPv4, TCP)
    if((serverfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        std::cerr << "socket failed" << std::endl;
        std::exit(EXIT_FAILURE);
    }
    
    // addressの設定
    address.sin_family = AF_INET; // IPv4を設定
    address.sin_addr.s_addr = htonl(INADDR_ANY);  // どのネットワーク装置からのアクセスも受け容れる
    address.sin_port = htons(PORT); // PORT番号を設定

    // bind
    if(bind(serverfd, (struct sockaddr *)&address, sizeof(address))<0)
    {
        std::cerr << "bind failed" << std::endl;
        std::exit(EXIT_FAILURE);
    }

    // listen clientは5つまで可 ただしプログラムは１対１通信
    if(listen(serverfd, 5) < 0)
    {
        std::cerr << "listen failed" << std::endl;
        std::exit(EXIT_FAILURE);
    }

    // accept
    if((clientfd = accept(serverfd, (struct sockaddr *)&address, (socklen_t *)&addr_len))<0)
    {
        std::cerr << "accept failed" << std::endl;
        std::exit(EXIT_FAILURE);
    }
    
    recv(clientfd, buffer, sizeof(buffer), 0); // データを受信
    std::cout << buffer << std::endl; // 受信したデータを表示

    send(clientfd, msg, sizeof(msg), 0); // msgを送信

    shutdown(serverfd, 2);

    return 0;
}