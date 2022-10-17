#include <iostream>

#define M 3
#define N 4
#define P 5

// Този алгоритъм с каква сложност е?
void multiplyMatrices( int matrix1[][ N ], int matrix2[][ P ] )
{
	for ( size_t i = 0; i < M; i++ )
	{
		for ( size_t j = 0; j < N; j++ )
		{
			printf( "%5d", matrix1[ i ][ j ] );
		}
		std::cout << std::endl;
	}
	std::cout << "\n*\n";
	for ( size_t i = 0; i < N; i++ )
	{
		for ( size_t j = 0; j < P; j++ )
		{
			printf( "%5d", matrix2[ i ][ j ] );
		}
		std::cout << std::endl;
	}
	int resultMatrix[ M ][ P ];

	for ( size_t i = 0; i < M; i++ )
	{
		for ( size_t j = 0; j < P; j++ )
		{
			resultMatrix[ i ][ j ] = 0;
			for ( size_t k = 0; k < N; k++ )
			{
				resultMatrix[ i ][ j ] += matrix1[ i ][ k ] * matrix2[ k ][ j ];
			}
		}
	}

	std::cout << "\n=\n";
	for ( size_t i = 0; i < M; i++ )
	{
		for ( size_t j = 0; j < P; j++ )
		{
			printf( "%5d", resultMatrix[ i ][ j ] );
		}
		std::cout << std::endl;
	}
}

int main()
{
	int matrix1[ M ][ N ];
	int matrix2[ N ][ P ];

	for ( size_t i = 0; i < M; i++ )
	{
		for ( size_t j = 0; j < N; j++ )
		{
			matrix1[ i ][ j ] = rand() % 10;
		}
	}

	for ( size_t i = 0; i < N; i++ )
	{
		for ( size_t j = 0; j < P; j++ )
		{
			matrix2[ i ][ j ] = rand() % 10;
		}
	}
	multiplyMatrices( matrix1, matrix2 );


	return 0;
}