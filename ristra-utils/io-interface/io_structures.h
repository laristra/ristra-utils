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
#include <stringstream>


/*!
  Super generic structure that can be adapted to store all kinds of data
  zero-copy interface for data

 */

struct Record
{
	std::string name;
	std::string datatype;	// int, float, double, ...
	size_t numElements;		
	std::string type;		//  ; can be NULL
	std::string desc;		// human readable description; can be NULL
	void *data;
	
	record(){};

	record(std::string _name, std::string _datatype, size_t _numElements, std::string _type, std::string _desc, void *_data)
	{
		name = _name;
		datatype = _datatype;
		numElements = _numElements;
		type = _type;
		desc = _desc;
		data = _data;
	}


	template <class T> T* getData(T* _data)
	{
		return ((T *)data);
	}


	std::string serialize()
	{
		std::stringstream ss;
		ss << name << " " << datatype << " " << numElements << " " << type << " " << desc << " ";

		if (datatype == "int")
		{
			for (int i=0; i<numElements; i++)
				ss << ((int *)data)[i] << " ";
		}
		else if (datatype == "float")
		{
			for (int i=0; i<numElements; i++)
				ss << ((float *)data)[i] << " ";
		}
		else if (datatype == "double")
		{
			for (int i=0; i<numElements; i++)
				ss << ((double *)data)[i] << " ";
		}
		else if (datatype == "size_t")
		{
			for (int i=0; i<numElements; i++)
				ss << ((size_t *)data)[i] << " ";
		}
		else if (datatype == "char")
		{
			for (int i=0; i<numElements; i++)
				ss << ((char *)data)[i];
		}
		
		ss << "\n";
		return ss.str();
	}
};



/*!
  Everything that is contant across all the timesteps of the simulation

 */

struct SimulationParams
{
	std::unordered_map<std::string, Record> field;
	
	int addAttribute(std::string name, std::string datatype, size_t numElements, std::string type, std::string desc, void * data)
	{
		Record x(name, datatype, numElements, type, desc, data);
		field.insert( {name, x} );

		return field.size();
	}
};



/*!
  Data that varies per timestep of the simulation

 */
struct TimestepData
{
	int timestep;
	timestep(){ timestep = 0; }

	std::unordered_map<std::string, Record> attribute;
	std::unordered_map<std::string, Record> dataField;


	int addAttribute(std::string name, std::string datatype, size_t numElements, std::string type, std::string desc, void * data)
	{
		Record x(name, datatype, numElements, type, desc, data);
		attribute.insert( {name, x} );

		return attribute.size();
	}


	int addDataField(std::string name, std::string datatype, size_t numElements, std::string type, std::string desc, void * data)
	{
		Record x(name, datatype, numElements, type, desc, data);
		dataField.insert( {name, x} );

		return dataField.size();
	}
};


} // namespace io-interface
} // namespace ristra