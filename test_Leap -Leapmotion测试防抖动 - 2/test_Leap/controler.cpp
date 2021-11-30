// #include "StdAfx.h"  // 
#include "controler.h"
// #include "StdAfx.h"  // 
SampleListener::SampleListener()
{
	Vector_obj.Initlize();        // Create a sample listener and controller
	controller2.addListener( *this ); 
	if_left_exist      = 0  ;
	if_right_exist     = 0  ; 
	Grasp_radius_Thre  = 84 ; // ץȡ�İ뾶��ֵ 
	if_Grasped_Flag    = 0  ; //  0����� 1 �������� 2 �������� 3����������ͬʱ  
	image_ok = false ; // 
}

SampleListener::SampleListener(SampleListener &self)
{
	Vector_obj.Initlize();        // Create a sample listener and controller
	controller2.addListener(self); // Have the sample listener receive events from the controller 
	if_left_exist      = 0  ;
	if_right_exist     = 0  ;
	Grasp_radius_Thre  = 84 ;
	if_Grasped_Flag    = 0  ; //  //  0����� 1 �������� 2 �������� 3����������ͬʱ 
}

void SampleListener::onInit(const Controller& controller) {
	std::cout << "Initialized" << std::endl;
	// controller2.addListener(controller); // Have the sample listener receive events from the controller
}

void SampleListener::onConnect(const Controller& controller) {
	std::cout << "Connected" << std::endl;
	controller.enableGesture(Gesture::TYPE_CIRCLE);
	controller.enableGesture(Gesture::TYPE_KEY_TAP);
	controller.enableGesture(Gesture::TYPE_SCREEN_TAP);
	controller.enableGesture(Gesture::TYPE_SWIPE);
}

void SampleListener::onDisconnect(const Controller& controller) {
	// Note: not dispatched when running in a debugger.
	std::cout << "Disconnected" << std::endl;
}

void SampleListener::onExit(const Controller& controller) {
	std::cout << "Exited" << std::endl;
}


void SampleListener::onFrame(const Controller& controller) 
{  
	const Frame frame = controller.frame(); 
	HandNum = frame.hands().count() ;


	timestamp  =    frame.currentFramesPerSecond() ;  
	// std::cout<<frame.timestamp() <<std::endl ;  

	if (    HandNum == 2    )   //   �ֵ�����  //  
	{   myFrameKnob =182 ; 	}

	HandList hands = frame.hands(); //   �����ж�����һֻ��  //  
	
	if_left_exist  = 0 ;
	if_right_exist = 0 ;
	if_Grasped_Flag = 0;  
	//    
	int appWidth = 800;
	int appHeight = 600; 
	//  
	InteractionBox iBox = frame.interactionBox();  // 
	Pointable pointable = frame.pointables().frontmost(); // ��leapmotion��3.0�汾�У�tool��ɾ������ //     
	Vector leapPoint = pointable.stabilizedTipPosition(); // ��leapmotion��3.0�汾�У�tool��ɾ������ // 
	bool leapPoint2  = pointable.isTool()  ;      // ��leapmotion��3.0�汾�У�tool��ɾ������ //  
	std::cout<< "*******************"  <<std::endl; 
	std::cout<< leapPoint2  <<std::endl; 
	std::cout<< leapPoint.x <<std::endl; 
	// Vector normalizedPoint = iBox.normalizePoint(leapPoint, false);

	Tool   frontTool  = frame.tools().frontmost(); 
	bool   LeapPoint  = frontTool.isTool() ;   
	std::cout << LeapPoint <<std::endl; 


	Leap::Tool tool = Leap::Tool::invalid();
	if (pointable.isTool()) {
		tool = Leap::Tool(pointable);  
		std::cout <<"**** "<<tool.stabilizedTipPosition().x <<std::endl ; 
	} 
	// 
	// 
	
	//             //
	//    tool     //
	//             //
	// ��leapmotion��3.0�汾�У�tool��ɾ������ //   
	//  
	// 
	
	// 
	// Uses Cinder OpenGL wrapper
	// frame = controller.frame();
	// 

	ImageList images = frame.images(); //  
	for(int i = 0; i < 2; i++)
	{
		Image image = images[i]; 
	    const unsigned char* image_buffer = image.data(); 
		height = image.height(); 
		width  = image.width();     
		std::cout << "height = " << height << std::endl ;  //    

	}
		//Draw the raw image data as a greyscale bitmap
		//   Surface surface(image.width(), image.height(), image.width() * 4, SurfaceChannelOrder::RGBA);
		//   int cursor = 0;
		// Surface::Iter iter = surface.getIter();
		/*  while( iter.line() ) {
		while( iter.pixel() ) {
		iter.r() = image_buffer[cursor];
		iter.g() = iter.b() = iter.r();
		iter.a() = 255;
		cursor++;
		}
		}
		*/ 

		////image_ok = false ; // 

	////ImageList images = frame.images(); 
	////for(int i = 0; i < 1; i++)
	////{ 
	////	Image image  =  images[i];
	////	image_buffer =  image.data(); //    
	////	
	////	height = image.height(); 
	////	width  = image.width();    

	////	std::cout << "height = " << height << std::endl ;  //    

	////	image_buffer_noconst =  (unsigned char *) malloc( height*width*sizeof(unsigned char ) ) ; 

	////	memcpy ( image_buffer_noconst , image_buffer , height*width*sizeof(unsigned char )  ) ;

	////	image_ok = true ; //  
	////	std::cout << "got it " << std::endl ;  //  
	////}
	//   
	//  
	for (  HandList::const_iterator hl = hands.begin(); hl != hands.end(); ++hl ) {  

		const Hand hand = *hl          ;  //  Get the first hand
		normal    = hand.palmNormal()  ;  //  Get the hand's normal vector
		direction = hand.direction ()  ;  //  palm direction  
		
		// direction = hand.translationProbability() ; //  

		// ���Ƶ��ٶ� // 
		hand.palmVelocity() ;  
		// position  = hand.stabilizedPalmPosition();   //  palm position  
		position               =  hand.palmPosition();  //  palm position  
		pos_bal =  hand.stabilizedPalmPosition() ; //  
		speed                  =  hand.palmVelocity() ;  // 
		// pos_bal =  hand.stabilizedPalmPosition() ; // 
		// 
		if( hand.isLeft() )
		{
			if_left_exist = 1 ;
			radius_hand_left = hand.sphereRadius();  
		}
		if( hand.isRight() )
		{
			if_right_exist = 1     ; // 
			radius_hand_right = hand.sphereRadius();  // 
			// double velocity = hand.stabilizedPalmPosition() ;
		}  
		myHandRollago =  myHandRoll      ;
		myHandRoll    =  normal.roll()   ;
		myHandYawago  =  myHandYaw       ; 
		myHandYaw     =  direction.yaw() ; 
	}  
	if(  (if_right_exist && radius_hand_right< Grasp_radius_Thre) ) 
	{
		if_Grasped_Flag = 1 ;// �κ�һ����ץ���˶���ץ���� 
	}
	if( ( if_left_exist && radius_hand_left< Grasp_radius_Thre)   )
	{
		if_Grasped_Flag = if_Grasped_Flag +  2 ; //  0����� 1 �������� 2 �������� 3����������ͬʱ 
	}


}

void SampleListener::onFocusGained(const Controller& controller) {
	std::cout << "Focus Gained" << std::endl;
}

void SampleListener::onFocusLost(const Controller& controller) {
	std::cout << "Focus Lost" << std::endl;
}

void SampleListener::onDeviceChange(const Controller& controller) {
	std::cout << "Device Changed" << std::endl;
	const DeviceList devices = controller.devices();
	for (int i = 0; i < devices.count(); ++i) { }
}

void SampleListener::onServiceConnect(const Controller& controller) {
	std::cout << "Service Connected" << std::endl;
}

void SampleListener::onServiceDisconnect(const Controller& controller) {
	std::cout << "Service Disconnected" << std::endl;
}
