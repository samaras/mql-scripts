#property copyright 	"Samuel Komfi, skomfi@gmail.com"
#property link 		"http://obrerosoft.com"

// OrderSend() - to open market and pending orders;
// OrderClose() and OrderCloseBy() - to close market orders
// OrderDelete() - to delete pending orders
// OrderModify() - to modify market and pending orders.

extern double lots = 0.01;
extern int takeprofit = 40;
extern int stoploss = 40;
extern int magic = 33454; // just a random number

//----------------------------------------------------------------+
// expert init function, runs when attaching to chart, runs once  +
//----------------------------------------------------------------+
int init()
{

	opensell();

	return (0);
}

//----------------------------------------------------------------+
// expert deinit function, runs only on detachment				  +
//----------------------------------------------------------------+
int deinit()
{

	return (0);
}

//----------------------------------------------------------------+
// expert start function, runs when a new tick arrives			  +
//----------------------------------------------------------------+
int start()
{
 
	return (0);
}

void opensell()
{
	// Builtin functions
	OrderSend(Symbol(), OP_SELL, lots, Bid, 3, Bid+stoploss*Point, Bid-takeprofit*Point, "Place Comment", magic, Blue);	
}

void openbuy()
{
	OrderSend(Symbol(), OP_BUY, lots, Ask, 3, Ask-stoploss*Point, Ask+takeprofit*Point, NULL, magic, Red);
}

/**
 * 
 * @param price
 * @param stop
 */
void openbuystop(double price, double stop)
{
	OrderSend(Symbol(), OP_BUYSTOP, lots, price, 3, stop, price+takeprofit*Point, NULL, magic, Pink);
}

/**
 * Delete your pending orders after a certain amount of time if not bought
 *
 * @return void
 */
void deletebuy()
{
	bool some = false;

	for (int i = 0; i < OrdersTotal(); i++)
	{
		OrderSelect(i, SELECT_BY_POS, MODE_TRADES);
		if(OrderType() == OP_BUYSTOP)
		{
			OrderDelete(OrderTicket(), Blue);
		}
	}
}

