/*********************************************************************

 *********************************************************************/

#include "MyApp.h"



MyApp::MyApp() {
  _sceneManager = NULL;
  _framelistener = NULL;
}

MyApp::~MyApp() {
  //delete _root;
  //delete _framelistener;
}

int MyApp::start() {
  _root = new Ogre::Root();
  Ogre::Root* aux = &Ogre::Root::getSingleton();
  if (!_root->restoreConfig()) {
    _root->showConfigDialog();
    _root->saveConfig();
  }
  Ogre::RenderWindow* window = _root->initialise(true, "BattleShip");
  _sceneManager = _root->createSceneManager(Ogre::ST_GENERIC,"mainSM");
  Ogre::Camera* cam = _sceneManager->createCamera("MainCamera");
  cam->setPosition(Ogre::Vector3(0.0f,2.0f,10.0f));
  cam->lookAt(Ogre::Vector3(0, 1, 0));
  cam->setNearClipDistance(5);
  cam->setFarClipDistance(100);

  Ogre::Viewport* viewport = window->addViewport(cam);
  viewport->setBackgroundColour(Ogre::ColourValue(0.0, 0.0, 0.0));
  double width = viewport->getActualWidth();
  double height = viewport->getActualHeight();
  cam->setAspectRatio(width / height);


  _sceneManager->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_MODULATIVE);
  _sceneManager->setShadowColour(Ogre::ColourValue(0.5, 0.5, 0.5));
  _sceneManager->setAmbientLight(Ogre::ColourValue(0.9, 0.9, 0.9));
  _sceneManager->setShadowTextureCount(2);
  _sceneManager->setShadowTextureSize(512);


  
  loadResources();
  createLight();




  
  _framelistener = new MyFrameListener(window);
  _root->addFrameListener(_framelistener);
  _root->startRendering();
  return 0;
}

void MyApp::loadResources() {
  Ogre::ConfigFile cf;
  cf.load("resources.cfg");

  std::cout << "Inicio de load resources" << std::endl;
  Ogre::ConfigFile::SectionIterator sI = cf.getSectionIterator();
  Ogre::String sectionstr, typestr, datastr;
  while (sI.hasMoreElements()) {
    sectionstr = sI.peekNextKey();
    Ogre::ConfigFile::SettingsMultiMap *settings = sI.getNext();
    Ogre::ConfigFile::SettingsMultiMap::iterator i;
    for (i = settings->begin(); i != settings->end(); ++i) {
      typestr = i->first;    datastr = i->second;
      Ogre::ResourceGroupManager::getSingleton().
          addResourceLocation(datastr, typestr, sectionstr);
    }
  }
  Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
}


void MyApp::createLight() {
  //_sceneManager->setAmbientLight(Ogre::ColourValue(1.0, 1.0, 1.0));


  Ogre::Light* light = _sceneManager->createLight("Light2");
  light->setPosition(0,5,5);
  light->setType(Ogre::Light::LT_SPOTLIGHT);
  light->setDirection(Ogre::Vector3(0,-0.5,-1));
  light->setSpotlightInnerAngle(Ogre::Degree(25.0f));
  light->setSpotlightOuterAngle(Ogre::Degree(60.0f));
  light->setSpotlightFalloff(0.0f);
  light->setCastShadows(true);
  
}
