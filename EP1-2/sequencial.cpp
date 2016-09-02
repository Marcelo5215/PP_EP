#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>
#include <iostream>
#include <list>


using namespace std;


std::list<long int> getPrimosSeq(int limite){
	list<long int> primes;
	int flag,i,j;

	primes.push_back(2);

	for(j=3;j<limite;j++){
		flag=0;
		//for(i=2;i<=sqrt(j);i++){
		//	if(j%i==0) flag=1;
		//}
		std::list<long int>::iterator i = primes.begin();
		while(*i<=sqrt(j)){
			if(j%*i==0){
				flag=1;
				break;
			}
			++i;
		}
		if(flag==0) primes.push_back(j);
	}	

	return primes;
}

int main(){
	int limit=10000000, time;
	struct timeval inicio, final;

	gettimeofday(&inicio, NULL);
	list<long int> primes = getPrimosSeq(limit);
	gettimeofday(&final, NULL);

	//for (std::list<long int>::iterator i = primes.begin(); i != primes.end(); ++i){
	//	cout << *i << ' ';
	//}
	//cout << endl;

	time = (int) (1000 * (final.tv_sec - inicio.tv_sec) + (final.tv_usec - inicio.tv_usec) / 1000);
	cout << time << endl;

	return 0;
}
