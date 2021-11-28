#ifndef STOCKS_H_SEEN
#define STOCKS_H_SEEN

typedef struct StockDataArray {
    struct StockData *stocks;
    int length;
    time_t refresh_time;
} StockDataArray;

typedef struct StockData {
    char symbol[24];
    char state[24];
    int error;
    double open;
    double price;
    double change;
    double change_perc;
    double volume;
    double volume_avg;
    double ebitda;
    double market_cap;
    double fifty_two_week_low;
    double fifty_two_week_high;
} StockData;

StockDataArray *StockDataArray_Create(char **symbols, int nsymbols);
void StockDataArray_Delete(StockDataArray *data);
void StockDataArray_Add(StockDataArray *data, char *symbol);

#endif