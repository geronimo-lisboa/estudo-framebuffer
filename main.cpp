#include <vtkObjectFactory.h>
#include<iostream>
#include <string>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSmartPointer.h>
#include <vtkActor.h>
#include <vtkCamera.h>

#include <boost/exception/all.hpp>

#include "myLightningTestActor.h"

#include <vtkDebugLeaks.h>

#include <vtkOpenGLRenderer.h>
#include <vtkRenderPass.h>
#include <vtkSequencePass.h>
#include <vtkCameraPass.h>
#include <vtkLightsPass.h>
#include <vtkDefaultPass.h>
#include <vtkRenderPassCollection.h>
#include <vtkTextureObject.h>
#include <vtkPixelBufferObject.h>


#include <vtkInteractorStyleTrackballCamera.h>
#include <boost\signals2.hpp>//O header da boost. Esse header precisa que sua lib seja inclusa.
#include <vtkImageData.h>
#include <vtkImageImport.h>
#include <vtkPNGWriter.h>

#include <vtkCylinderSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>

int main(int argc, char **argv){
	try{
		// This creates a polygonal cylinder model with eight circumferential facets
		// (i.e, in practice an octagonal prism).
		vtkSmartPointer<vtkCylinderSource> cylinder = vtkSmartPointer<vtkCylinderSource>::New();
		cylinder->SetResolution(8);
		// The mapper is responsible for pushing the geometry into the graphics library.
		// It may also do color mapping, if scalars or other attributes are defined.
		vtkSmartPointer<vtkPolyDataMapper> cylinderMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
		cylinderMapper->SetInputConnection(cylinder->GetOutputPort());
	// The actor is a grouping mechanism: besides the geometry (mapper), it
		// also has a property, transformation matrix, and/or texture map.
		// Here we set its color and rotate it around the X and Y axes.
		vtkSmartPointer<vtkActor> cylinderActor = vtkSmartPointer<vtkActor>::New();
		cylinderActor->SetMapper(cylinderMapper);
		cylinderActor->GetProperty()->SetColor(1.0000, 0.3882, 0.2784);
		cylinderActor->RotateX(30.0);
		cylinderActor->RotateY(-45.0);
		// The renderer generates the image
		// which is then displayed on the render window.
		// It can be thought of as a scene to which the actor is added
		vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
		renderer->AddActor(cylinderActor);
		renderer->SetBackground(0.1, 0.2, 0.4);
		// Zoom in a little by accessing the camera and invoking its "Zoom" method.
		renderer->ResetCamera();
		renderer->GetActiveCamera()->Zoom(1.5);
		// The render window is the actual GUI window
		// that appears on the computer screen
		vtkSmartPointer<vtkRenderWindow> renderWindow =	vtkSmartPointer<vtkRenderWindow>::New();
		renderWindow->SetSize(200, 200);
		renderWindow->AddRenderer(renderer);
		// The render window interactor captures mouse events
		// and will perform appropriate camera or actor manipulation
		// depending on the nature of the events.
		vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
		renderWindowInteractor->SetRenderWindow(renderWindow);
		// This starts the event loop and as a side effect causes an initial render.
		renderWindowInteractor->Start();



		//vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
		//vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
		//vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
		//renderWindow->AddRenderer(renderer);
		//renderWindow->SetInteractor(renderWindowInteractor);
		//vtkSmartPointer<myLightiningTestActor> mapperMassinha = vtkSmartPointer<myLightiningTestActor>::New();
		//#ifdef AVELL
		//mapperMassinha->SetData("C:\\programacao\\estudo-framebuffer\\assets\\Massinha Teste.obj", "C:\\programacao\\estudo-framebuffer\\assets\\teste_tex.png");
		//mapperPlano->SetData("C:\\programacao\\estudo-framebuffer\\assets\\plano.obj", "C:\\programacao\\estudo-framebuffer\\assets\\teste_tex.png");
		//#endif
		//#ifdef MEDILAB
		//mapperMassinha->SetData("C:\\teste\\estudo-framebuffer\\assets\\Massinha Teste.obj", "C:\\teste\\estudo-framebuffer\\assets\\teste_tex.png");
		//#endif
		//mapperMassinha->SetPosition(1, 0, 0);
		//renderer->SetBackground(0.5, 0, 0);
		//renderer->AddActor(mapperMassinha);
		//renderWindow->SetSize(200, 200);
		//renderer->ResetCamera();
		//vtkCamera *cam = renderer->GetActiveCamera();
		//renderer->GetActiveCamera()->ParallelProjectionOn();
		//cam->SetClippingRange(0.0001, 10);
		//cam->Dolly(2);
		//cam->SetViewAngle(45);
		//renderWindow->Render();
		//renderWindowInteractor->Start();
	}
	catch (boost::exception &ex)
	{
		std::cout << boost::diagnostic_information(ex) << std::endl;
	}
	catch(std::exception &ex)
	{
		std::cout << ex.what() << std::endl;
	}
	catch(...)
	{
		std::cout << "alguma exeção misteriosa aconteceu..." << std::endl;
	}


	vtkDebugLeaks::SetExitError(0);
	if (vtkDebugLeaks::PrintCurrentLeaks() != 0)
		std::cout << "tem leaks..." << std::endl;
	return EXIT_SUCCESS;
}