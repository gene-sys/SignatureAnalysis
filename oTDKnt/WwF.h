extern void gFuncTest(LPTSTR ref, BOOL EnableShow);  //������� ������� ��������������� �����
//extern BOOL gExitFuncTest();  //������� �������� ���������������� ����� �� ���������� ��������
extern CString gResultTest(BOOL bDiaOrSig);  //������� ������ ���������� �������������
//�������� ������� ��������������� ��������������� �����
extern CString r_Opn; //���� � ����������� ������ ��������
extern CString strWR; //������ ���� � ������� ������� �����
extern CString strTF; //��� ����� ������� ��������
extern CString strTD; //��� ����� ������� ����������
extern int intNT; //���������� ������ � ������ (�������� ����������)
extern UINT iCountTest; //���������� ������ � ������ (�������� �� 3 �� 1)
extern UINT iCountDTest; //���������� ��������� � ������ (�������� �� 5 �� 1)
extern CString csNodeName; //��� ��������� ��� ������ ����� ������
extern BOOL bHideShowTest; //������/���������� ���� �����
extern BOOL bCycleCheck; // ���������/ �� ��������� ������� ������ � ������
extern BOOL bAutoCheck; //������� � �������������
//����� ��� ��������� ���������
extern COLORREF G_WRITESIG;
extern COLORREF G_ALERT;
extern COLORREF G_INFORMATION;
extern COLORREF G_MESSAGE; 
extern void Sort(CStringArray* HN,UINT index); //���������� ��������
extern CString csHead; // ���������
