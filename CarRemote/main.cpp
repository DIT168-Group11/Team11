#include <gtkmm.h>
#include <iostream>
#include <cstdint>
#include <chrono>
#include <sstream>
#include <thread>
#include "cluon/OD4Session.hpp"
#include "cluon/Envelope.hpp"
#include "messages.hpp"

cluon::OD4Session *od4remote;

using namespace std;

opendlv::proxy::GroundSteeringReading msgAngle;
opendlv::proxy::PedalPositionReading msgSpeed;

float motorSpeed = 0.15;
float servoAngle= 15;
const float motorStop = 0.0;

void onClick_forward();
void onClick_stop();
void onClick_right();
void onClick_left();

void remote(cluon::OD4Session *od4){
    cout << "--MOVING VEHICLE--" << endl;

    msgAngle.steeringAngle(servoAngle);
    od4->send(msgAngle);
    msgSpeed.percent(motorSpeed);
    od4->send(msgSpeed);
    this_thread::sleep_for(chrono::milliseconds(1000));
}

void stop(cluon::OD4Session *od4){
    cout << "--STOPPING VEHICLE--" << endl;
    msgSpeed.percent(motorStop);
    od4->send(msgSpeed);
}


void forward(cluon::OD4Session *od4){

    cout << "--MOVING FORWARD--" << endl;
    msgAngle.steeringAngle(0);
    od4->send(msgAngle);
    msgSpeed.percent(motorSpeed);
    od4->send(msgSpeed);

}

void left(cluon::OD4Session *od4){

    cout << "--TURNING LEFT--" << endl;
    msgAngle.steeringAngle(servoAngle);
    od4->send(msgAngle);
    msgSpeed.percent(motorSpeed);
    od4->send(msgSpeed);
}

void right(cluon::OD4Session *od4){

    cout << "--TURNING RIGHT--" << endl;
    msgAngle.steeringAngle(-(servoAngle));
    od4->send(msgAngle);
    msgSpeed.percent(motorSpeed);
    od4->send(msgSpeed);
}

int main(int argc, char* argv[]){
	od4remote = new cluon::OD4Session(221, [](cluon::data::Envelope &&envelope) noexcept {});

	Gtk::Main kit(argc,argv);

	Gtk::Window window;
	Gtk::Box box;
	Gtk::Button forward("FORWARD");
	Gtk::Button left("LEFT");
	Gtk::Button right("RIGHT");
	Gtk::Button stop("STOP");

	window.set_default_size(400, 60);
	window.set_title("GROUP_11 RC");
	window.set_border_width(10);
	window.set_position(Gtk::WIN_POS_CENTER);

	Gtk::Box frame1;
	Gtk::Box frame2;
	Gtk::Label label1, label2;

	label1.set_text("Move Commands:  ");
	label2.set_text("Steer Commands:  ");
	frame1.add(label1);
	frame2.add(label2);
	frame1.add(forward);
	frame1.add(stop);
	frame2.add(left);
	frame2.add(right);

	window.add(box);
	box.pack_start(frame1);
	box.pack_start(frame2);

	forward.signal_pressed().connect(
		sigc::ptr_fun(&onClick_forward)
		);

	forward.signal_released().connect(
		sigc::ptr_fun(&onClick_stop)
		);

	right.signal_pressed().connect(
		sigc::ptr_fun(&onClick_right)
		);

	right.signal_released().connect(
		sigc::ptr_fun(&onClick_stop)
		);

	left.signal_pressed().connect(
		sigc::ptr_fun(&onClick_left)
		);

	left.signal_released().connect(
		sigc::ptr_fun(&onClick_stop)
		);

	stop.signal_pressed().connect(
		sigc::ptr_fun(&onClick_stop)
		);

	stop.signal_released().connect(
		sigc::ptr_fun(&onClick_stop)
		);

	window.show_all_children();

	Gtk::Main::run(window);

	return 0;
}

void onClick_forward(){
	cout << "<< FORWARD CLICKED >>" << endl;
	forward(od4remote);
}

void onClick_right(){
	cout << "<< RIGHT CLICKED >>" << endl;
	right(od4remote);

}

void onClick_left(){
	cout << "<< LEFT CLICKED >>" << endl;
	left(od4remote);
}

void onClick_stop(){
	cout << "<< STOP CLICKED >>" << endl;
        stop(od4remote);
}
