#include <cstdlib>
#include <iostream>
#include "list.cpp"


using namespace std;



		
	int main()
	 {
		
		List<int> lst;
		cout<<"������� ������ ������  "<<endl;
		int size, enter;
		cin>>size;
		for(int i = 0;i<size;i++)
			{
			cout<<"������� "<<i+1<<" �����"<<endl;
			cin>>enter;
			lst.Add(enter);
			cout<<endl;
			}

		List <int> :: Iterator it;
		for(auto &Elem:lst)
			{
				Elem--;
			}
		
		it=lst.begin();
		cout<< *it<<endl;
		lst.Show();
	}