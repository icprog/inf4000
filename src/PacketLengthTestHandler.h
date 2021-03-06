///////////////////////////////////////////////////////////////////////////////////
// PacketLengthTestHandler
// Inherite FeatureTestHandler virtual class and has all information concerning 
// 	the packet size test.
///////////////////////////////////////////////////////////////////////////////////
#ifndef _PACKETLENGTHTESTHANDLER_H_
#define _PACKETLENGTHTESTHANDLER_H_

#include <map>
#include <stdint.h>

#include "FeatureTestHandler.h"

class PacketLengthTestHandler: public FeatureTestHandler
{
	public:
		PacketLengthTestHandler(fs::fstream *modelFile, fs::path path, int typeOfTest);
		~PacketLengthTestHandler();
		virtual void initCapture();
		virtual void JsonToData(Json::Value * json);
		virtual void runTest(double cAlpha);
		virtual int getTestResult();	
		virtual void computePacket(const struct pcap_pkthdr* pkthdr, const unsigned char * packet );
		std::map<uint32_t ,uint32_t>* getModelDistribution() const;
		std::map<uint32_t ,uint32_t>* getTestDistribution() const;
		void computeModelMaxValue();
		void computeTestMaxValue();
		virtual Json::Value *DataToJson() const;
		void printDistribution() const;
	private:
		uint32_t getModelSampleSize();
		uint32_t getTestSampleSize();
		std::map <uint32_t,uint32_t> *modelDist_;
		std::map <uint32_t,uint32_t> *testDist_;
		std::vector<double> *modelCumulDist_;
		std::vector<double> *testCumulDist_;
		size_t maxModelSize_;
		double dStat_;
		double cAlpha_;
		double seuil_;
		size_t maxTestSize_;
		static const double BUFFER; // 1*10^-15
};
#endif
