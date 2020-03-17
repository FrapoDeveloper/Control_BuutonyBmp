#include <windows.h>
#define ID_LABEL 100
#define ID_BTNSALIR 101
LRESULT CALLBACK ProcediementoVentana(HWND hwnd,UINT msg, WPARAM wParam,LPARAM lParam);
int WINAPI WinMain(HINSTANCE hIns,HINSTANCE hInstanciaPrevia,LPSTR lpCmdLinea,int nCmdShow){
    HWND ventana,hiconUser;
    HBITMAP hlogoBinario;
    MSG mensaje;
    WNDCLASSEX clase;
    clase.cbSize = sizeof(WNDCLASSEX);
    clase.cbClsExtra = 0;
    clase.style = CS_HREDRAW | CS_VREDRAW;
    clase.lpfnWndProc = ProcediementoVentana;
    clase.hInstance = hIns;
    clase.hIcon = LoadIcon(NULL,0);
    clase.hIconSm =LoadIcon(NULL,IDI_INFORMATION);
    clase.hCursor = LoadCursor(NULL,IDC_ARROW);
    clase.lpszClassName = "IdentificadorVentana";
    clase.hbrBackground =CreateSolidBrush( RGB(21,232,189));
    if(!RegisterClassEx(&clase)){
        MessageBox( NULL,"No se pudo ejecutar la aplicacion","Error",MB_ICONERROR);
        return EXIT_FAILURE;
    }

    ventana = CreateWindowEx(0,"IdentificadorVentana","Controles",WS_OVERLAPPEDWINDOW |WS_SYSMENU,
                            400,80,580,630,HWND_DESKTOP,NULL,hIns,NULL);
    CreateWindowW(L"Static",L"Ingrese un numero : ",WS_VISIBLE | WS_CHILD , 90,100,150,20,ventana,NULL,hIns,NULL);
    CreateWindowEx(0,"EDIT","",ES_NUMBER|ES_AUTOHSCROLL|ES_LEFT|WS_CHILD|WS_VISIBLE,250,100,40,20,ventana,NULL,hIns,NULL);
    CreateWindowW(L"Static",L"Ingrese un numero : ",WS_VISIBLE | WS_CHILD  , 90,150,150,20,ventana,NULL,hIns,NULL);
    CreateWindowEx(0,"EDIT","",ES_NUMBER|ES_AUTOHSCROLL|ES_LEFT|WS_CHILD|WS_VISIBLE,250,150,40,20,ventana,NULL,hIns,NULL);
    CreateWindowEx(0,"BUTTON","Salir del programa",BS_CENTER|WS_VISIBLE|WS_CHILD,400,550,150,30,ventana,(HMENU)ID_BTNSALIR,NULL,NULL);

    ShowWindow(ventana,nCmdShow);
    UpdateWindow(ventana);

    while(GetMessage(&mensaje,NULL,0,0)>0){
            TranslateMessage(&mensaje);
            DispatchMessage(&mensaje);
    }
}

LRESULT CALLBACK ProcediementoVentana(HWND hwnd,UINT msg, WPARAM wParam,LPARAM lParam){
    HWND himg;
    HBITMAP cargar_img;
    cargar_img= (HBITMAP)LoadImageW(NULL,L"calculator.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);

   static HINSTANCE Instancia;
    switch(msg){
                case WM_CREATE:{

                            Instancia =((LPCREATESTRUCT)lParam)->hInstance;


                            himg = CreateWindowW(L"Static",NULL,WS_VISIBLE | WS_CHILD | SS_BITMAP, 80,340,0,0,hwnd,NULL,Instancia,NULL);
                            SendMessageW(himg,STM_SETIMAGE,IMAGE_BITMAP,(LPARAM) cargar_img);

                          break;
                }

                case WM_COMMAND:{
                   switch(LOWORD(wParam)){
                        case ID_BTNSALIR:{
                            if(MessageBox(hwnd,"¿Desea salir del programa?","Salir.",MB_OKCANCEL|MB_ICONQUESTION)==IDOK){
                                SendMessage(hwnd,WM_DESTROY,0,0);
                            }



                        }


                    }

                    break;
                }

                case WM_DESTROY:{
                PostQuitMessage(0);
                        break;
                }

                case WM_CTLCOLORSTATIC:{
                    HDC hdcStatic = (HDC) wParam;
                    SetTextColor(hdcStatic, RGB(0,0,0));
                    SetBkColor(hdcStatic,RGB(21,232,189));
                    return (INT_PTR)CreateSolidBrush(RGB(21,232,189));
                    break;
                }




                default:{
                return DefWindowProc(hwnd, msg,wParam,lParam);
                }
    }
    return 0;
}

