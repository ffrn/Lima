//###########################################################################
// This file is part of LImA, a Library for Image Acquisition
//
// Copyright (C) : 2009-2011
// European Synchrotron Radiation Facility
// BP 220, Grenoble 38043
// FRANCE
//
// This is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 3 of the License, or
// (at your option) any later version.
//
// This software is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, see <http://www.gnu.org/licenses/>.
//###########################################################################
#include "SimuHwInterface.h"

using namespace lima;
using namespace std;

/*******************************************************************
 * \brief SimuDetInfoCtrlObj constructor
 *******************************************************************/

SimuDetInfoCtrlObj::SimuDetInfoCtrlObj(Simulator& simu)
	: m_simu(simu)
{
}

SimuDetInfoCtrlObj::~SimuDetInfoCtrlObj()
{
}

void SimuDetInfoCtrlObj::getMaxImageSize(Size& max_image_size)
{
	FrameDim fdim;
	m_simu.getFrameDim(fdim);
	max_image_size = fdim.getSize();
}

void SimuDetInfoCtrlObj::getDetectorImageSize(Size& det_image_size)
{
	m_simu.getMaxImageSize(det_image_size);
}

void SimuDetInfoCtrlObj::getDefImageType(ImageType& def_image_type)
{
	FrameDim fdim;
	m_simu.getFrameDim(fdim);
	def_image_type = fdim.getImageType();
}

void SimuDetInfoCtrlObj::setCurrImageType(ImageType curr_image_type)
{
	FrameDim fdim;
	m_simu.getFrameDim(fdim);
	fdim.setImageType(curr_image_type);
	m_simu.setFrameDim(fdim);
}

void SimuDetInfoCtrlObj::getCurrImageType(ImageType& curr_image_type)
{
	FrameDim fdim;
	m_simu.getFrameDim(fdim);
	curr_image_type = fdim.getImageType();
}

void SimuDetInfoCtrlObj::getPixelSize(double& pixel_size)
{
	pixel_size = 1e-6;
}

void SimuDetInfoCtrlObj::getDetectorType(string& det_type)
{
	det_type = "Simulator";
}

void SimuDetInfoCtrlObj::getDetectorModel(string& det_model)
{
	det_model = "PeakGenerator";
}

void SimuDetInfoCtrlObj::registerMaxImageSizeCallback(
						HwMaxImageSizeCallback& cb)
{
	m_mis_cb_gen.registerMaxImageSizeCallback(cb);
}

void SimuDetInfoCtrlObj::unregisterMaxImageSizeCallback(
						HwMaxImageSizeCallback& cb)
{
	m_mis_cb_gen.unregisterMaxImageSizeCallback(cb);
}


void SimuDetInfoCtrlObj::
     MaxImageSizeCallbackGen::setMaxImageSizeCallbackActive(bool cb_active)
{
}


/*******************************************************************
 * \brief SimuBufferCtrlObj constructor
 *******************************************************************/

SimuBufferCtrlObj::SimuBufferCtrlObj(Simulator& simu)
	: m_simu(simu), 
	  m_buffer_mgr(simu.getBufferMgr())
{
}

SimuBufferCtrlObj::~SimuBufferCtrlObj()
{
}

void SimuBufferCtrlObj::setFrameDim(const FrameDim& frame_dim)
{
	m_buffer_mgr.setFrameDim(frame_dim);
}

void SimuBufferCtrlObj::getFrameDim(FrameDim& frame_dim)
{
	m_buffer_mgr.getFrameDim(frame_dim);
}

void SimuBufferCtrlObj::setNbBuffers(int nb_buffers)
{
	m_buffer_mgr.setNbBuffers(nb_buffers);
}

void SimuBufferCtrlObj::getNbBuffers(int& nb_buffers)
{
	m_buffer_mgr.getNbBuffers(nb_buffers);
}

void SimuBufferCtrlObj::setNbConcatFrames(int nb_concat_frames)
{
	m_buffer_mgr.setNbConcatFrames(nb_concat_frames);
}

void SimuBufferCtrlObj::getNbConcatFrames(int& nb_concat_frames)
{
	m_buffer_mgr.getNbConcatFrames(nb_concat_frames);
}

void SimuBufferCtrlObj::getMaxNbBuffers(int& max_nb_buffers)
{
	m_buffer_mgr.getMaxNbBuffers(max_nb_buffers);
}

void *SimuBufferCtrlObj::getBufferPtr(int buffer_nb, int concat_frame_nb)
{
	return m_buffer_mgr.getBufferPtr(buffer_nb, concat_frame_nb);
}

void *SimuBufferCtrlObj::getFramePtr(int acq_frame_nb)
{
	return m_buffer_mgr.getFramePtr(acq_frame_nb);
}

void SimuBufferCtrlObj::getStartTimestamp(Timestamp& start_ts)
{
	m_buffer_mgr.getStartTimestamp(start_ts);
}

void SimuBufferCtrlObj::getFrameInfo(int acq_frame_nb, HwFrameInfoType& info)
{
	m_buffer_mgr.getFrameInfo(acq_frame_nb, info);
}

void SimuBufferCtrlObj::registerFrameCallback(HwFrameCallback& frame_cb)
{
	m_buffer_mgr.registerFrameCallback(frame_cb);
}

void SimuBufferCtrlObj::unregisterFrameCallback(HwFrameCallback& frame_cb)
{
	m_buffer_mgr.unregisterFrameCallback(frame_cb);
}


/*******************************************************************
 * \brief SimuSyncCtrlObj constructor
 *******************************************************************/

SimuSyncCtrlObj::SimuSyncCtrlObj(Simulator& simu)
	: HwSyncCtrlObj(), m_simu(simu)
{
}

SimuSyncCtrlObj::~SimuSyncCtrlObj()
{
}

bool SimuSyncCtrlObj::checkTrigMode(TrigMode trig_mode)
{
	return (trig_mode == IntTrig);
}

void SimuSyncCtrlObj::setTrigMode(TrigMode trig_mode)
{
	if (!checkTrigMode(trig_mode))
		throw LIMA_HW_EXC(InvalidValue, "Invalid (external) trigger");
}

void SimuSyncCtrlObj::getTrigMode(TrigMode& trig_mode)
{
	trig_mode = IntTrig;
}

void SimuSyncCtrlObj::setExpTime(double exp_time)
{
	m_simu.setExpTime(exp_time);
}

void SimuSyncCtrlObj::getExpTime(double& exp_time)
{
	m_simu.getExpTime(exp_time);
}

void SimuSyncCtrlObj::setLatTime(double lat_time)
{
	m_simu.setLatTime(lat_time);
}

void SimuSyncCtrlObj::getLatTime(double& lat_time)
{
	m_simu.getLatTime(lat_time);
}

void SimuSyncCtrlObj::setNbHwFrames(int nb_frames)
{
	m_simu.setNbFrames(nb_frames);
}

void SimuSyncCtrlObj::getNbHwFrames(int& nb_frames)
{
	m_simu.getNbFrames(nb_frames);
}

void SimuSyncCtrlObj::getValidRanges(ValidRangesType& valid_ranges)
{
	double min_time = 10e-9;;
	double max_time = 1e6;
	valid_ranges.min_exp_time = min_time;
	valid_ranges.max_exp_time = max_time;
	valid_ranges.min_lat_time = min_time;
	valid_ranges.max_lat_time = max_time;
}


/*******************************************************************
 * \brief SimuBinCtrlObj constructor
 *******************************************************************/

SimuBinCtrlObj::SimuBinCtrlObj(Simulator& simu)
	: m_simu(simu)
{
}

SimuBinCtrlObj::~SimuBinCtrlObj()
{
}

void SimuBinCtrlObj::setBin(const Bin& bin)
{
	m_simu.setBin(bin);
}

void SimuBinCtrlObj::getBin(Bin& bin)
{
	m_simu.getBin(bin);
}

void SimuBinCtrlObj::checkBin(Bin& bin)
{
	m_simu.checkBin(bin);
}


/*******************************************************************
 * \brief SimuHwInterface constructor
 *******************************************************************/

SimuHwInterface::SimuHwInterface(Simulator& simu)
	: m_simu(simu), m_det_info(simu), m_buffer(simu), 
	  m_sync(simu), m_bin(simu)
{
	HwDetInfoCtrlObj *det_info = &m_det_info;
	m_cap_list.push_back(HwCap(det_info));

	HwBufferCtrlObj *buffer = &m_buffer;
	m_cap_list.push_back(HwCap(buffer));

	HwSyncCtrlObj *sync = &m_sync;
	m_cap_list.push_back(HwCap(sync));

	HwBinCtrlObj *bin = &m_bin;
	m_cap_list.push_back(HwCap(bin));
}

SimuHwInterface::~SimuHwInterface()
{
}

void SimuHwInterface::getCapList(HwInterface::CapList &aReturnCapList) const
{
  aReturnCapList = m_cap_list;
}

void SimuHwInterface::reset(ResetLevel reset_level)
{
	m_simu.reset();
}

void SimuHwInterface::prepareAcq()
{
}

void SimuHwInterface::startAcq()
{
	m_simu.startAcq();
}

void SimuHwInterface::stopAcq()
{
	m_simu.stopAcq();
}

void SimuHwInterface::getStatus(StatusType& status)
{
	Simulator::Status simu_status = m_simu.getStatus();
	switch (simu_status) {
	case Simulator::Ready:
		status.acq = AcqReady;
		status.det = DetIdle;
		break;
	case Simulator::Exposure:
		status.det = DetExposure;
		goto Running;
	case Simulator::Readout:
		status.det = DetReadout;
		goto Running;
	case Simulator::Latency:
		status.det = DetLatency;
	Running:
		status.acq = AcqRunning;
		break;
	}
	status.det_mask = DetExposure | DetReadout | DetLatency;
}

int SimuHwInterface::getNbHwAcquiredFrames()
{
	return m_simu.getNbAcquiredFrames();
}

