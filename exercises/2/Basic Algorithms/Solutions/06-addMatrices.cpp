#include <iostream>

#define M 3
#define N 4

// Този алгоритъм с каква сложност е?
void addMatrices( int matrix1[][ N ], int matrix2[][ N ] )
{
	for ( size_t i = 0; i < M; i++ )
	{
		for ( size_t j = 0; j < N; j++ )
		{
			printf( "%5d", matrix1[ i ][ j ] );
		}
		std::cout << std::endl;
	}
	std::cout << "\n+\n";
	for ( size_t i = 0; i < M; i++ )
	{
		for ( size_t j = 0; j < N; j++ )
		{
			printf( "%5d", matrix2[ i ][ j ] );
		}
		std::cout << std::endl;
	}
	int resultMatrix[ M ][ N ];

	for ( size_t i = 0; i < M; i++ )
	{
		for ( size_t j = 0; j < N; j++ )
		{
			resultMatrix[ i ][ j ] = matrix1[ i ][ j ] + matrix2[ i ][ j ];
		}
	}

	std::cout << "\n=\n";
	for ( size_t i = 0; i < M; i++ )
	{
		for ( size_t j = 0; j < N; j++ )
		{
			printf( "%5d", resultMatrix[ i ][ j ] );
		}
		std::cout << std::endl;
	}
}

int main()
{
	int matrix1[ M ][ N ];
	int matrix2[ M ][ N ];

	for ( size_t i = 0; i < M; i++ )
	{
		for ( size_t j = 0; j < N; j++ )
		{
			matrix1[ i ][ j ] = i * j;
			matrix2[ i ][ j ] = i * -3;
		}
	}
	addMatrices( matrix1, matrix2 );


	return 0;
}