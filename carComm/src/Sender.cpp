#include "Sender.hpp"

int main(int argc, char** argv) {
	using namespace std;

	cluon::OD4Session od4(111, [](cluon::data::Envelope) noexcept {});
	//input arguments from main
	if (argc > 1) {

		uint16_t val = stoi(argv[1]);
		MyTestMessage1 message;
		message.myValue(val);
		od4.send(message);
		std::cout << "Message Sent!\n";

	} else {

		// Send 3 random numbers
		int i = 0;
		while (i < 3) {
			uint16_t randomNum;
			std::cout << "\n --Sending a new message-- \n";
			std::cout << "Generating random number... \n";
			randomNum = rand();
			std::cout << "The magic number is: " << randomNum << "\n";
			//std::cin >> randomNum;

			MyTestMessage1 message;
			message.myValue(randomNum);
			od4.send(message);
			std::cout << "\n Sent! \n";
			i++;
			std::this_thread::sleep_for(3s);
		}
	}

	return 0;
}
