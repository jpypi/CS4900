#include "app.h"

void App::Init()
{
  //put initialization stuff here

	HRESULT hr; //Stores HRESULT returned by functions.

	hr = GetDefaultKinectSensor(&m_sensor);
	if (FAILED(hr)) {
		printf("Failed to find a Kinect sensor!\n");
		exit(-5);
	}

	//Open the sensor.
	m_sensor->Open();

	//Set up DepthFrameSource.
	//Need this to open a DepthFrameReader.
	IDepthFrameSource* depthFrameSource;
	hr = m_sensor->get_DepthFrameSource(&depthFrameSource);
	if (FAILED(hr)) {
		printf("Failed to get depth frame source. \n");
		exit(-5);
	}

	//Get frame description from DepthFrameSource.
	IFrameDescription *frameDescription;
	depthFrameSource->get_FrameDescription(&frameDescription);
	//Ignoring error checking due to small probability.
	frameDescription->get_Width(&m_depthWidth);
	frameDescription->get_Height(&m_depthHeight);
	


	//Set up DepthFrameReader.
	hr = depthFrameSource->OpenReader(&m_depthFrameReader);
	if (FAILED(hr)) {
		printf("Failed to open depth frame reader. \n");
	}

	SafeRelease(depthFrameSource);

	//Initialize depth buffer.
	m_depthBuffer = new uint16[(m_depthWidth * m_depthHeight)];
}

void App::Tick(float deltaTime)
{
  //update and drawing stuff here

	HRESULT hr;

	IDepthFrame* depthFrame;
	hr = m_depthFrameReader->AcquireLatestFrame(&depthFrame);

	//Program runs faster than Kinect can grab frames. So if error, just continue.
	if (FAILED(hr)) {
		return;
	}

	//Copy data to the depth buffer. Capacity is in elements not in bytes.
	//printf("Copying data to buffer!\n"); //Use for debug to confirm data is being copied for each tick.
	hr = depthFrame->CopyFrameDataToArray( 
		(m_depthWidth * m_depthHeight) , m_depthBuffer
	);
	if (FAILED(hr)) {
		SafeRelease(depthFrame);
		printf("Warning! Something went wrong while copying to buffer!\n");
		return;
	}
	SafeRelease(depthFrame);

	//Copy Depth data to the window.
	for (int i = 0; i < (m_depthWidth * m_depthHeight) ; i++) {
		uint16 d_value = m_depthBuffer[i];

		//Take only rightmost byte of depth data and
		// set as RGB value to make grayscale projection.
		uint8 a = d_value & 0xff;
		m_pixelBuffer[i] = (a << 16) | (a << 8) | a;
	}


}

void App::Shutdown()
{
  //put cleaning up stuff here

	delete[] m_depthBuffer;	 
	SafeRelease(m_depthFrameReader);
	SafeRelease(m_sensor);
}
