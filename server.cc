// To use this executable:
// ./executable_name port_number

#include <iostream>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <chrono>
#include <thread>

void error( const char *message ) {
    perror( message );
    exit( 1 );
}

// TODO: Eventually break apart this hideous function
int bind_socket( int argc, char* argv[] ) {
     char buffer[ 256 ];
     int val{};
     int sock{};
     int new_sock{};
     int port_number{};

     ssize_t n{};
     socklen_t client_length{};

     struct sockaddr_in server_address{};
     struct sockaddr_in client_address{};

     if ( argc < 2 ) {
         fprintf( stderr,"ERROR, no port provided\n" );
         exit( 1 );
     }

     // Open socket
     sock = socket( PF_INET, SOCK_STREAM, 0 );

     if ( sock < 0 )
        error("ERROR opening socket");

     // Specify address reuse in the event of rapid connect/disconnect
     setsockopt( sock, SOL_SOCKET, SO_REUSEADDR, &val, sizeof( val ) );

     // Clear address structure
     memset( &server_address, 0, sizeof( server_address ) );

     // Convert command line argument (port number) to integer
     port_number = std::stoi( std::string{ argv[ 1 ] } );

     // Populate address structure
     server_address.sin_family      = AF_INET;    // IPv4
     server_address.sin_addr.s_addr = INADDR_ANY; // Accept any address
     server_address.sin_port        = htons( static_cast<uint16_t>( port_number ) ); // Convert to network byte order

     // Bind socket
     if ( bind( sock, reinterpret_cast<struct sockaddr *> ( &server_address ), sizeof( server_address ) ) < 0 )
              error("ERROR on binding");

     // Listen for incoming connections
     listen( sock, 5 );

     client_length = sizeof( client_address );
     new_sock = accept( sock, reinterpret_cast<struct sockaddr *>( &client_address ), &client_length );

     if ( new_sock < 0 )
          error("ERROR on accept");

     int connection_count = 0;
     while( ++connection_count < 100 ) {
          n = read( new_sock, buffer, sizeof( buffer ) - 1 );

          if( n > 0 ) connection_count = 0;

          std::cout << buffer << std::endl;
          memset( &buffer, 0, sizeof( buffer ) );
     }

     close( new_sock );
     close( sock );
}

int main( int argc, char *argv[] ) {
     bind_socket( argc, argv );
     return 0; 
}

