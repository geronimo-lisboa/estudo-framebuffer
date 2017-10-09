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


int main(int argc, char **argv){
	try{
		vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
		vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
		vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
		renderWindow->AddRenderer(renderer);
		renderWindow->SetInteractor(renderWindowInteractor);
		vtkSmartPointer<myLightiningTestActor> mapperMassinha = vtkSmartPointer<myLightiningTestActor>::New();
		#ifdef AVELL
		mapperMassinha->SetData("C:\\programacao\\estudo-framebuffer\\assets\\Massinha Teste.obj", "C:\\programacao\\estudo-framebuffer\\assets\\teste_tex.png");
		mapperPlano->SetData("C:\\programacao\\estudo-framebuffer\\assets\\plano.obj", "C:\\programacao\\estudo-framebuffer\\assets\\teste_tex.png");
		#endif
		#ifdef MEDILAB
		mapperMassinha->SetData("C:\\teste\\estudo-framebuffer\\assets\\Massinha Teste.obj", "C:\\teste\\estudo-framebuffer\\assets\\teste_tex.png");
		#endif
		mapperMassinha->SetPosition(1, 0, 0);
		renderer->SetBackground(0.5, 0, 0);
		renderer->AddActor(mapperMassinha);
		renderWindow->SetSize(200, 200);
		renderer->ResetCamera();
		vtkCamera *cam = renderer->GetActiveCamera();
		renderer->GetActiveCamera()->ParallelProjectionOn();
		cam->SetClippingRange(0.0001, 10);
		cam->Dolly(2);
		cam->SetViewAngle(45);
		renderWindow->Render();
		renderWindowInteractor->Start();
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