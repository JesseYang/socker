#include <ruby.h>
#include <iostream>
#include <string.h>    //strlen
#include <sys/socket.h>
#include <arpa/inet.h> //inet_addr
#include <thread>

using namespace std;

thread t;

static VALUE object_send_request(VALUE rb_self, VALUE remote_ip, VALUE port, VALUE content) {

	// convert argments type
	char *remote_ip_str = RSTRING_PTR(remote_ip);
	int port_int = NUM2INT(port);
	char *content_str = RSTRING_PTR(content);
	

	int socket_desc, recv_byte_num;
	struct sockaddr_in server;
	char server_reply[2000];
	VALUE ret_val;

	cout << "Begin to send request in C" << endl;
	// create socket
	socket_desc = socket(AF_INET, SOCK_STREAM, 0);
	if (socket_desc == -1)
	{
		cout << "Cound not create socket" << endl;
	}

	server.sin_addr.s_addr = inet_addr(remote_ip_str);
	server.sin_family = AF_INET;
	server.sin_port = htons(port_int);

	// connect to remote server
	if (connect(socket_desc, (struct sockaddr *)&server, sizeof(server)) < 0)
	{
		cout << "connect error" << endl;
		return 1;
	}
	cout << "Connected" << endl;

	// send some data
	if (send(socket_desc, content_str, strlen(content_str), 0) < 0)
	{
		cout << "Send failed" << endl;
		return -1;
	}
	cout << "Data Send" << endl;

	// receive a reply from the server
	recv_byte_num = recv(socket_desc, server_reply, 2000, 0);
	if (recv_byte_num < 0)
	{
		cout << "recv failed" << endl;
	}
	cout << "reply received" << endl;
	cout << server_reply << endl;

	// return
	ret_val = rb_str_new(server_reply, recv_byte_num);
	return ret_val;
}

static VALUE object_start_server(VALUE rb_self, VALUE port) {

	int port_int = NUM2INT(port);
	int socket_desc, new_socket, c;
	struct sockaddr_in server, client;
	char *message;

	// create a socket
	socket_desc = socket(AF_INET, SOCK_STREAM, 0);
	if (socket_desc == -1)
	{
		cout << "could not create socket" << endl;
	}

	// prepare the sockaddr_in structure
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(port_int);

	// bind
	if (::bind(socket_desc, (struct sockaddr *)&server, sizeof(server)) < 0)
	{
		cout << "bind failed" << endl;
	}
	cout << "bind done" << endl;

	// listen
	listen(socket_desc, 3);

	// accept any incoming connection
	cout << "waiting for incoming connections..." << endl;
	c = sizeof(struct sockaddr_in);
	new_socket = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c);
	if (new_socket < 0)
	{
		cout << "accept failed" << endl;
	}

	cout << "connection accepted" << endl;

	// reply to the client
	message = "Hello Client , I have received your connection. But I have to go now, bye\n";
	write(new_socket , message , strlen(message));

	return 0;
}

static VALUE object_test_callback(VALUE rb_self) {
	// Get the method's symbol
	ID sym_mymethod = rb_intern("say_hi");
	// Call the method, giving 3 parameters
	VALUE result = rb_funcall(rb_self, sym_mymethod, 0);
}

static void test_thread(VALUE rb_self) {
	for (int i = 0; i < 10; i++) {
		cout << i << endl;
		// Get the method's symbol
		ID sym_mymethod = rb_intern("say_hi");
		// Call the method, giving 3 parameters
		VALUE result = rb_funcall(rb_self, sym_mymethod, 0);
		sleep(1);
	}
}

static thread create_thread(VALUE rb_self) {
	thread t1(&test_thread, rb_self);
	return t1;
}

static VALUE object_test_thread(VALUE rb_self) {
	t = create_thread(rb_self);
	t.join();
}

extern "C" void Init_socker_in_c() {
	rb_define_method(rb_cObject, "send_request_in_c", (VALUE(*)(ANYARGS))object_send_request, 3);
	rb_define_method(rb_cObject, "start_server_in_c", (VALUE(*)(ANYARGS))object_start_server, 1);
	rb_define_method(rb_cObject, "test_callback_in_c", (VALUE(*)(ANYARGS))object_test_callback, 0);
	rb_define_method(rb_cObject, "test_thread_in_c", (VALUE(*)(ANYARGS))object_test_thread, 0);
}
