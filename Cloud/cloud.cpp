#include "cloud.hpp"

int main()
{
	cloud_sys::Client client("121.5.43.223",9000);
	client.Start();
	return 0;
}



