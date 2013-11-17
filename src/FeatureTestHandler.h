#ifndef _FEATURECAPTURE_H_
#define _FEATURECAPTURE_H_

#include <fstream>
#include <vector>
#include <string>

#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
#include "../libs/jsoncpp/json/json.h"

#include "PacketCapture.h"

namespace fs = boost::filesystem ;
class FeatureTestHandler {
	public:
		FeatureTestHandler(fs::fstream *modelFile, fs::path path, int typeOfTest);
		virtual void initCapture() = 0;
		void loadDataToModel();
		void saveDataToModel();
		virtual void computePacket(const struct pcap_pkthdr* pkthdr, const unsigned char * packet ) = 0;
		virtual void printDistribution() const = 0;
		virtual void runTest() = 0;
		virtual int getTestResult() = 0;
		virtual void JsonToData(Json::Value * json) = 0;
		virtual Json::Value *DataToJson() const = 0;
		std::string getFeatureName() const;
		void setFeatureName(std::string name);
		PacketCapture* getPacketCapture() const;
		void addPacketCaptureFile(FILE * pcapFile);
		fs::fstream *getModelFile()const;
		void setTypeOfData(int type);
		int getTypeOfData() const;
		
	private:
		PacketCapture *pcap_;
		fs::path path_;
		fs::fstream *modelFile_;
		std::string FEATURE_NAME;
		int typeOfData_;

	protected:
		static const std::string MODEL_ROOT_;
};
#endif
