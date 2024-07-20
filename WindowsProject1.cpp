// WindowsProject1.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

// win32API는 GDI를 이용해서 그리기 작업을 함
// DC에 출력하기 위하여 GDI 오브젝트를 사용
// DC -> 도화지
// GDI Object -> 그림 도구

// gdi는 비트맵
// gdi++ jpg, png
// -> cpu를 이용해서 렌더

// 이후 부터 그래픽 라이브러리
// directX, openGL, vulkan 등
// -> gpu를 이용한 렌더

// GDI Object 종류는 크게 6개
// HPEN : 선을 그릴 때 사용
// HBRUSH : 어떠한 도형을 그리고, 면에 패턴이나 색을 채울 때 사용
// HFONT : 문자 출력에 사용
// HBITMAP : 비트맵 이미지 출력할 때 사용
// HPALETTE : win32API를 이용하여 개발할 때, 동시에 출력할 수 있는
// 색상의 제약을 극복하기 위해 팔레트에 256가지의 색상을 저장해서 사용 했었음
// 현재는 최소 트루 컬러를 사용하기 때문에 사용할 일이 없음
// HRGN : 화면 상의 영역을 나타낼 때 사용

// GDI Object를 사용할 때, 규칙
// 사용할 DC 영역에 사용할 GDI Object를 등록하여 사용하며,
// 사용 시, 마지막에 등록한 GDI Object가 사용됩니다.
// 사용이 끝났다면 메모리 관리를 위하여 해제시켜야 합니다.
// -> DC에 GDI Object가 등록된 상태라면 해제가 불가능

// DC에 오브젝트 등록
// HGDIOBJ SelectObject(HDC hdc, HGDIOBJ obj)를 사용하여 오브젝트를 등록
// SelectObject를 사용하게 된다면 hdc에 obj를 선택시키고, 사용하고 있었던
// 같은 종류의 오브젝트를 반환해줌

// GDI 오브젝트 해제
// BOOL DeleteObject(HGDIOBJ obj)를 이용하여 해제

// Stock Object 스톡 오브젝트
// 운영체제가 미리 만들어서 관리하는 GDI 오브젝트를 말합니다.
// 아주 빈번하게 사용되므로 운영체제가 부팅할 때부터 미리 만들어 놓습니다.
// 만들지 않아도 언제든지 사용할 수 있으며, 운영체제가 관리하기 때문에
// 사용하고 난 후에 해제할 필요가 없습니다.

// HGDIOBJ GetStockObject(int fnObject)를 사용하여 스톡 오브젝트의
// 핸들러를 가져올 수 있음
// fnObject에는 스톡 오브젝트의 미리 정의된 키 값을 전달


#include "framework.h"
#include "WindowsProject1.h"
#include "MainGame.h"

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.
HWND g_hWnd;

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

// WinMain -> 콘솔에서 main과 같이 프로그램 시작 시, 가장 먼저 들어오는 엔트리 포인트
// hInstance : 프로그램의 인스턴스 핸들
// 인스턴스란?
// 클래스가 메모리에 실제로 구현된 실체를 의미
// windows용 프로그램은 여러 개의 프로그램이 동시에 실행되는
// 멀티테스킹 시스템이며, 하나의 프로그램을 여러번 실행할 수도 있습니다.
// 이 때, 실행되고 있는 각각의 프로그램을 Program Instance 라고 표현

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WINDOWSPROJECT1, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWSPROJECT1));

    MSG msg;
	msg.message = WM_NULL;

	MainGame mainGame;
	// 메인 게임 객체 초기화
	mainGame.Initialize();

    // 기본 메시지 루프입니다:
	// 발생한 이벤트를 메세지로 받아들여서 처리한다. (이벤트 드리븐)

	// 큐(Queue)에 대해
	// 선입선출(FIFO) 방식의 자료구조 (먼저 들어간 데이터가 먼저 출력 됨)

	// GetMessage()가 하는 작업
	// 메세지 큐는 키보드나 마우스를 통해 발생하는 메시지를 저장하기 위해
	// 할당된 큐 입니다.
	// 메세지 큐에서 메세지를 가져오고, 가져온 메세지를 큐에서 제거하며
	// 만약 가져온 메세지가 WM_QUIT 이라면 0 (FALSE)를 반환하고,
	// 그 외 메세지라면 1(TRUE) 를 리턴합니다.
	// 또, 에러 발생 시 -1을 리턴
	// -> 리턴 값을 통해 메세지 루프를 제어

	// GetMessage는 만약 메세지 큐에서 대기 중인 처리되지 않은 메세지가 없다면
	// 메세지 큐에 메세지가 발생하여 들어올 때까지 무한히 대기하며,
	// 이러한 특징 때문에 일반적인 응용프로그램에서는 GetMessage() 사용해도 무관하지만
	// 게임 개발이 목적이라면 GetMessage 보다 PickMessage 를 사용
	// -> PickMessage 사용 시, 처리할 메세지가 있다면 처리를 하되,
	//    없다면 다른 작업을 할 수 있습니다.

	// 게임 로직 갱신에 사용할 틱 타임
	ULONGLONG updateTime = GetTickCount64();

	// 윈도우 메세지가 종료 메세지가 아니라면 반복
    while (msg.message != WM_QUIT)
    {
        if (PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
		else
		{
			auto currentTime = GetTickCount64();

			if (updateTime + 10 < currentTime)
			{
				// 이전 갱신 시간을 현재 시간으로 갱신
				updateTime = currentTime;

				// 게임 로직 업데이트 및 렌더
				mainGame.Update();
				mainGame.Render();
			}
		}
    }

    return (int) msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWSPROJECT1));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WINDOWSPROJECT1);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   // 윈도우 창 사이즈 정의
   RECT rc = { 0, 0, WIN_SIZE_X, WIN_SIZE_Y };
   AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, true);

   // 윈도우 창을 생성하고, 생성된 창의 핸들러를 반환합니다.
   // 또, 추가적인 윈도우 창이 있다면 해당 창의 핸들러에 넘겨 나중에
   // 객체(창)를 구분할 수 있도록 해야합니다.
   // 그러므로 생성한 창의 핸들을 보관할 수 있도록, hWnd 에 담아두는 작업이 필요
   HWND hWnd = CreateWindowW(
	   szWindowClass, // 윈도우 클래스 이름
	   szTitle, // 윈도우 타이틀 (창 이름)
	   WS_OVERLAPPEDWINDOW, // 생성할 창의 스타일을 지정
      CW_USEDEFAULT, 0, // 창의 왼쪽 상단이 화면의 어느 위치에 위치하도록 할 것인지 x, y 좌표
	   rc.right - rc.left, rc.bottom - rc.top, // 창의 해상도 설정 (너비, 높이)
	   // 부모 윈도우의 핸들을 지정 (부모가 있다면)
	   // 하나의 프로그램에서 여러개의 윈도우 창을 쓸 경우
	   // or 하나의 프로그램 실행 시, 다중으로 여러 프로그램을 자동으로 실행시켜
	   // 다른 프로그램의 창과 정보를 연결시킬 때 사용
	   nullptr, 
	   // 메뉴 핸들러를 지정
	   nullptr, 
	   // 윈도우 식별자를 지정 (main에서 받은 윈도우 인스턴스를 전달)
	   hInstance, 
	   // 여러 개의 윈도우를 만들 때, 파라미터를 전달할 구조체에 대한 포인터
	   // 일반적으로 한 개의 윈도우만 만들 것이므로 nullptr로 지정
	   nullptr);

   g_hWnd = hWnd;

   if (!hWnd)
   {
      return FALSE;
   }

   // 윈도우 창 활성화/표시
   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...

			//Rectangle(hdc, 100, 100, 200, 200);
			//Ellipse(hdc, 300, 300, 400, 400);

            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
		// 위에서 처리하지 않은 메세지들은 기본적인 처리방식으로 처리할 수 있도록 합니다.
		// 발생한 모든 메세지에 대한 처리를 할 수 없으므로
		// 위의 케이스가 아닌 메세지에 대한 처리를 알아서 하도록 합니다.
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
