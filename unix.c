#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <dirent.h>

#define MAX_LINE 200

int main()
{
   //const char *commandsAccepted[] = { "ls", "-l", "cat", "&", "!!", "sort", "|", NULL };
   int should_run = 1;
   char args[ MAX_LINE/2 + 1 ], copia[ MAX_LINE/2 + 1 ], args2[ MAX_LINE/2 + 1 ], commands[ 5 ][ 80/2 + 1 ], historial[ MAX_LINE/2 + 1 ];
   memset( historial, 0, MAX_LINE/2 + 1 );
   memset( args2, 0, MAX_LINE/2 + 1 );
   FILE *fin;
   while( should_run == 1 )
   {
      printf( "osh>" );
      fgets( args, MAX_LINE/2 + 1, stdin );
      strcpy( copia, args );
      if( strcmp( args, "!!\n" ) == 0 )
      {
         if( historial[ 0 ] == '\0' )
         {
            printf( "No hay comandos en el historial.\n" );
         }
         else{
            strcpy( args, historial );
         }
      }
      int i, j = 0, k = 0;
      for( i = 0; i < strlen( args ); i++, j++ )
      {
         if( args[ i ] != ' ' && args[ i ] != '\n' )
         {
            char temp;
            temp = args[ i ];
            args2[ j ] = temp;
         }
         else{
            j = -1;
            strcpy( commands[ k ], args2 );
            memset( args2, 0, MAX_LINE/2 + 1 );
            k = k + 1;
         }
      }
      if( strcmp( commands[ 0 ], "cat" ) == 0 )
      {
         if( !( fin = fopen( commands[ 1 ], "r" ) ) )
            printf( "Error al abrir el fichero.\n" );
         else{
            char linea[ 500 ];
            fgets( linea, sizeof( linea ), fin );
            while( !feof( fin ) ) 
            {
               printf( "%s\n", linea );
               fgets( linea, sizeof( linea ), fin );
            }
            printf( "%s\n", linea );
            fclose( fin );
         }
      }
      else if( strcmp( commands[ 0 ], "-ls" ) == 0 )
      {
         DIR *d;
         struct dirent *dir;
         char fullpath[ PATH_MAX + 1 ];
         int total;
         j = 0;
         if( strcmp( commands[ 1 ], "-l" ) == 0 )
         {
            if( strcmp( commands[ 2 ], ">" ) == 0 )
            {
               total = 10 + strlen( commands[ 3 ] );
               memset( args2, 0, MAX_LINE/2 + 1 );
               for( i = total; i < strlen( copia ) - 1; i++, j++ )
               {
                  char temp;
                  temp = copia[ i ];
                  args2[ j ] = temp;
               }
               fin = fopen( commands[ 3 ], "w" );
               if( ( d = opendir( args2 ) ) != NULL )
               {
                  while( ( dir = readdir( d ) ) != NULL )
                  {
                     realpath( dir->d_name, fullpath );
                     //printf( "[%s]\n", fullpath );
                     fprintf( fin, "%s ", dir->d_name );
                  }
                  perror( "Something isn't working: " );
                  closedir( d );
                  fclose( fin );
               }
            }
            else{
               total = 7;
               memset( args2, 0, MAX_LINE/2 + 1 );
               for( i = total; i < strlen( copia ) - 1; i++, j++ )
               {
                  char temp;
                  temp = copia[ i ];
                  args2[ j ] = temp;
               }
               if( ( d = opendir( args2 ) ) != NULL )
               {
                  while( ( dir = readdir( d ) ) != NULL )
                  {
                     realpath( dir->d_name, fullpath );
                     //printf( "[%s]\n", fullpath );
                     printf( "%s ", dir->d_name );
                  }
                  perror( "Something isn't working: " );
                  closedir( d );
               }
               else
                  printf( "Ocurrio un error al tratar de abrir la direccion.\n" );
            }
         }
         else if( strcmp( commands[ 1 ], ">" ) == 0 )
         {
            total = 7 + strlen( commands[ 2 ] );
            memset( args2, 0, MAX_LINE/2 + 1 );
            for( i = total; i < strlen( copia ) - 1; i++, j++ )
            {
               char temp;
               temp = copia[ i ];
               args2[ j ] = temp;
            }
            fin = fopen( commands[ 2 ], "w" );
            if( ( d = opendir( args2 ) ) != NULL )
            {
               while( ( dir = readdir( d ) ) != NULL )
               {
                  realpath( dir->d_name, fullpath );
                  //printf( "[%s]\n", fullpath );
                  fprintf( fin, "%s\n", dir->d_name );
               }
               perror( "Something isn't working: " );
               closedir( d );
               fclose( fin );
            }
         }
         else
         {
            total = 4;
            memset( args2, 0, MAX_LINE/2 + 1 );
            for( i = total; i < strlen( copia ) - 1; i++, j++ )
            {
               char temp;
               temp = copia[ i ];
               args2[ j ] = temp;
            }
            if( ( d = opendir( args2 ) ) != NULL )
            {
               while( ( dir = readdir( d ) ) != NULL )
               {
                  realpath( dir->d_name, fullpath );
                  //printf( "[%s]\n", fullpath );
                  printf( "%s\n", dir->d_name );
               }
               perror( "Something isn't working: " );
               closedir( d );
            }
         }
      }
      strcpy( historial, args );
      memset( args2, 0, MAX_LINE/2 + 1 );
      memset( args, 0, MAX_LINE/2 + 1 );
   }
   
   return 0;
}