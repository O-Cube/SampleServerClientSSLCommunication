# SampleServerClientSSLCommunication
Demonstrates encrypted communication between client and server.
![image](https://github.com/O-Cube/SampleServerClientSSLCommunication/assets/65163799/8a804a46-04f4-4327-9223-586e36e1e3b0)
Components:
  - Server Certificate and Private Key ccreated and signed with openssl.
  - Certificate Authority created with openssl.
  - MySslServer as server. Perform listening on 127.0.0.1 with port 60001.
  - MyClient as a client. Communicates with server on 127.0.0.1 with port 60002.
  - Wireshark.
Operation:
  - Client connects to server and initiates SSL communication using Tls1.3. SSL handshake is successful and server transmits a minimal
message to client and closes the connection. 
![image](https://github.com/O-Cube/SampleServerClientSSLCommunication/assets/65163799/57d57e2d-c567-43eb-85b9-1fb5d263dfdf)


