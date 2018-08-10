/*
  _____________       _____              _____  _________________
  ___  __ \__(_)________  /_____________ __  / / /_  /___(_)__  /_______
  __  /_/ /_  /__  ___/  __/_  ___/  __ `/  / / /_  __/_  /__  /__  ___/
  _  _, _/_  / _(__  )/ /_ _  /   / /_/ // /_/ / / /_ _  / _  / _(__  )
  /_/ |_| /_/  /____/ \__/ /_/    \__,_/ \____/  \__/ /_/  /_/  /____/

  Copyright (c) 2018 Los Alamos National Security, LLC
  All rights reserved.
                                                                              */

#pragma once


namespace ristra {
namespace io-interface {


#include <string>
#include <iostream>
#include <sstream>
#include <vector> 
#include <stdexcept>
#include <mpi.h>
#include <fstream>
#include <typeinfo>


#include "timer.hpp"

#include "interface.h"
#include "io_interface.h"

//#include "posixIO.hpp"
//#include "mpiIO.hpp"
//#include "structuredGrid.h"


class IOInterface
{
	std::string filename;
	std::string commType;	// MPI or Legion

	std::string backend;
	unsigned fileIOType;

	int numSimParams;
	int numAttributes;
	int numDataFields;

	MPI_Comm comm;
	// something for Legion

	SimulationParams sim;
	TimestepData tsData;


	std::stringstream log;

  public:
  	Interface *ioMgr;

  	enum Backend 
	{
		IO_POSIX = 0,
		IO_MPI = 1,
		IO_VTK = 2
	};


	IOInterface(std::string _backend);
	~IOInterface(){ };

	int init(std::string _filename, std::string _commType);		// mode: read or write
	void setMPIComm(MPI_Comm _comm){ comm = _comm; }
	void setLegionComm();

	int addSimParameter(std::string name, std::string datatype, size_t numElements, std::string type, std::string desc, void * data);
	int addAttribute(std::string name, std::string datatype, size_t numElements, std::string type, std::string desc, void * data);
	int addFieldData(std::string name, std::string datatype, size_t numElements, std::string type, std::string desc, void * data);

	int write(int ts);
	int read(int ts);

	std::string getLog(){ return log.str(); }
};



IOInterface::IOInterface(std::string _backend):backend(_backend)
{
	if (backend == "POSIX")
	{
		fileIOType = IO_POSIX;
		//ioMgr = new POSIX_IO();	
	}
	
	else if (backend == "VTK_STURCTURED_GRID")
	{
		fileIOType = IO_VTK;
		//ioMgr = new StructuredGrid();
	}
	else if (backend == "MPI_IO")
	{
		fileIOType = IO_MPI;
		//ioMgr = new MPIIO();
	}
	else
	{
		throw std::runtime_error("Backend not supported! Please choose either \"POSIX\" or \"MPI_IO\" ");
	}

	numSimParams = 0;
	numAttributes = 0;
	numDataFields = 0;
}


inline int init(std::string _filename, std::string _commType)
{
	Timer clock;
	clock.start();

	filename = _filename;
	commType = _commType;

	clock.stop();
	log << "File open took " << clock.getDuration() << " s"<< std::endl;
}




inline int IOInterface::addSimParameter(std::string name, std::string datatype, size_t numElements, std::string type, std::string desc, void * data)
{
	Timer clock;
	clock.start();

	sim.addAttribute(name, datatype, numElements, type, desc, data);
	numSimParams++;

	clock.stop();
	log << "Add sim parameter " << clock.getDuration() << " s"<< std::endl;
}


inline int IOInterface::addAttribute(std::string name, std::string datatype, size_t numElements, std::string type, std::string desc, void * data)
{
	Timer clock;
	clock.start();
	
	tsData.addAttribute(name, datatype, numElements, type, desc, data);
	numAttributes++;

	clock.stop();
	log << "Add ts attribute " << clock.getDuration() << " s"<< std::endl;
}


inline int IOInterface::addFieldData(std::string name, std::string datatype, size_t numElements, std::string type, std::string desc, void * data)
{
	Timer clock;
	clock.start();
	
	tsData.addDataField(name, datatype, numElements, type, desc, data);
	numDataFields++;

	clock.stop();
	log << "Add ts fields data " << clock.getDuration() << " s"<< std::endl;
}



inline int IOInterface::write(int ts)
{
	Timer clock;
	clock.start();
 
	if (ts == 0)	// only write simulation parameters at the first timestep
		ioMgr->writeDataset(simData);

	tsData.timestep = ts;
	ioMgr->writeTimestepData(tsData);

	clock.stop();
	log << "Writing to disk took " << clock.getDuration() << " s"<< std::endl;
}


inline int IOInterface::read(int ts)
{

}


} // namespace io-interface
} // namespace ristra