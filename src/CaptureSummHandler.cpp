#include <pcap.h>

#include "CaptureSummHandler.h"
#include "utils.h"

using namespace std;

CaptureSummHandler::CaptureSummHandler(fs::fstream *modelFile, fs::path path, int typeOfTest):FeatureTestHandler(modelFile, path, typeOfTest){
	nbOfPackets_ = 0;
	beginning_ = 0;
	duration_ = 0;
	setFeatureName("CAPTURE_SUMMARY");
}
CaptureSummHandler::~CaptureSummHandler(){}
void CaptureSummHandler::initCapture(){}
void CaptureSummHandler::computePacket(const struct pcap_pkthdr* pkthdr, const unsigned char * packet ){
	nbOfPackets_++;
	if(beginning_ == 0)
		beginning_ = timevalToUINT64(pkthdr->ts);
	else
		duration_ = timevalToUINT64(pkthdr->ts) - beginning_;

}
void CaptureSummHandler::JsonToData(Json::Value * json){
	//Intentionnaly not reading the number of packet 
	//from the file since it only really make sence to 
	//display number of packet in analysis mode
}
Json::Value *CaptureSummHandler::DataToJson() const {
	return new Json::Value(nbOfPackets_);;
}
void CaptureSummHandler::runTest(double cAlpha){}
int CaptureSummHandler::getTestResult(){
	cout<<"Number of packet captured: "<<nbOfPackets_<<endl;
	//cout<<"Duration of the capture: "<<duration_<<" µs."<<endl;
	return 0;
}
void CaptureSummHandler::printDistribution() const{}