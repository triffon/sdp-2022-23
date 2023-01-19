#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>

void rearrangeBarcodes( const std::vector<int>& barcodes )
{
    using FreqBarcodePair    = std::pair< size_t, int >;
    using BarcodeFreqPair    = std::pair< int, size_t >;

    std::unordered_map<int, size_t>         freqsMap;
    std::priority_queue< FreqBarcodePair >  maxHeap;

    for ( int barcode : barcodes )
        ++freqsMap[ barcode ];

    for ( const BarcodeFreqPair& mapPair : freqsMap )
        maxHeap.push( std::make_pair( mapPair.second, mapPair.first ) );

    FreqBarcodePair max;
    FreqBarcodePair nextMax;
    while ( !maxHeap.empty() )
    {
        max = maxHeap.top();
        maxHeap.pop();
        std::cout << max.second << " ";
        --max.first;

        if ( !maxHeap.empty() )
        {
            nextMax = maxHeap.top();
            maxHeap.pop();
            std::cout << nextMax.second << " ";
            --nextMax.first;
        }

        if ( max.first > 0 )
            maxHeap.push( max );

        if ( nextMax.first > 0 )
            maxHeap.push( nextMax );
    }
}


int main()
{
    rearrangeBarcodes( { 1, 1, 1, 2, 2, 2 } );
    std::cout << "\n";
    rearrangeBarcodes( { 1, 3, 4, 2, 2, 2 } );
    std::cout << "\n";
    rearrangeBarcodes( { 1, 1, 1, 1, 2, 2, 3, 3 } );

    return 0;
}
