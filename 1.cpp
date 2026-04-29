#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
using namespace std;

int main(){
	/* current_direction is -1 when turning left, and 1 when turning right.
	current_distance tracks the current distance to turn.
	position tracks the position of the dial.
	zeros tracks the number of times the dial has touched zero. */
	int current_direction;
	int current_distance;
	int position = 50;
	int zeros = 0;
	// line tracks the current line of ifstream input
	string line;
	ifstream input ("input.txt");

	if(input.is_open()){
		while (getline(input,line)){
			if (line.at(0) == 'L'){
				current_direction = -1;
			} else {
				current_direction = 1;
			}

			/* All 100-degree rotations cause the total number of zeros to increase by 1, and they also send the dial to its original position
			 * before that rotation. So we'll subtract them one by one from the total rotation distance, and increment zeros each time.
			 * Then, we need to make sure that the distance is NOT zero. Because that would give us extra zeros.
			 * From there, we handle the case where position starts at zero by adding current_direction and then making sure position is in range.
			 * In cases where position does not start at zero, and adding current_direction gives a number outside [0, 99], we do have to add another zero when
			 * pushing position back into its range.
			 */
			current_distance = stoi(line.substr(1));
			while (current_distance > 99){
				zeros++;
				current_distance -= 100;
			}
			if (current_distance != 0){
				if (position == 0){
					position += current_distance * current_direction;
					if (position > 99){
						position -= 100;
					} else if (position < 0){
						position += 100;
					}
				} else {
					position += current_distance * current_direction;
					if (position > 99){
						position -= 100;
						zeros++;
					} else if (position < 0){
						position += 100;
						zeros++;
					} else if (position == 0) zeros++;
				}
			}
			cout << "\nRotation: " << line;
			cout << "\nZeros: " << zeros;
			cout << "\nPosition: " << position;
			cout << "\n";
		}
		input.close();
	} else cout << "Unable to open file";
	cout << "\n" << zeros << "\n";
	return 0;
}
