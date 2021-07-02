#include"defines.h"

//write code for testing our final Lidar Module
//

int main() {
	if(ishealthok()) {
		std::vector<int> temp=scandata();
		for(int i=0;i<360;i++){
			printf("%d : %d\n",i,temp[i]);
		}
	}
	else {
		printf("Error in Lidar......\n");
	}
	
	
	return 0;
}

