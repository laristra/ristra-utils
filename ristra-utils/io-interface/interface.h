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

#include <iostream>
#include <sstream>
#include <string>
#include <stdexcept>
#include <cstring>
#include <vector>
#include <unordered_map>

#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <mpi.h>

#include "io_structures.h"


class Interface
{
  protected:
  	std::string filename;
  	std::string commType;	// MPI or Legion
	
  public:
  	virtual void init(std::string filename, std::string _commType) = 0;

	virtual void writeDataset(SimulationParams s) = 0;
	virtual void writeTimestepData(TimestepData t) = 0;

	virtual void readDataset(SimulationParams s) = 0;
	virtual void readTimestepData(TimestepData t) = 0;
};

} // namespace io-interface
} // namespace ristra