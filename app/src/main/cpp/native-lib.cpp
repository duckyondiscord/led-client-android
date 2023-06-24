#include <jni.h>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>

#define SERVER_IP "46.214.239.71"
#define SERVER_PORT 8000

extern "C" JNIEXPORT jstring JNICALL
Java_org_ducky_ledclient_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    int client_socket;
    struct sockaddr_in server_address;
    char message[5] = "test";
    char server_response[1024];

    // Create a socket
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        perror("Socket creation failed");
        return env->NewStringUTF("Socket creation failed");
    }

    // Set up server address
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(SERVER_PORT);
    if (inet_pton(AF_INET, SERVER_IP, &(server_address.sin_addr)) <= 0) {
        perror("Invalid address or address not supported");
        return env->NewStringUTF("Invalid address or address not supported");
    }

    // Connect to the server
    if (connect(client_socket, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
        perror("Connection failed");
        return env->NewStringUTF("Failed to connect to server, idk ask ducky lol, knowing him it's probably not running");
    }

    // Send the message to the server
    if (send(client_socket, message, strlen(message), 0) < 0) {
        perror("Message sending failed");
        return env->NewStringUTF("Failed to send message, now I really don't know how you got here.");
    }

    // Receive response from the server
    if (recv(client_socket, server_response, sizeof(server_response), 0) < 0) {
        perror("Response receiving failed");
        return env->NewStringUTF("Well I sent the message but didn't get a reply, so it's anybody's guess whether the LED flashed or not");
    }
    printf("Server response: %s\n", server_response);
    // Close the socket
    close(client_socket);

    return env->NewStringUTF(server_response);
}