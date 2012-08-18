extern void gFuncTest(LPTSTR ref, BOOL EnableShow);  //функция запуска первоначального теста
//extern BOOL gExitFuncTest();  //функция закрытия первоначалльного теста по завершению процесса
extern CString gResultTest(BOOL bDiaOrSig);  //функция вывода результата тестировоания
//описание запуска первоначального функционального теста
extern CString r_Opn; //путь к открываемым файлам деревьев
extern CString strWR; //строка пути к текущей рабочей папке
extern CString strTF; //имя файла шаблона сигнатур
extern CString strTD; //имя файла шаблона диагностик
extern int intNT; //количество тестов в файлах (остается постоянным)
extern UINT iCountTest; //количество тестов в файлах (меняется от 3 до 1)
extern UINT iCountDTest; //количество диатестов в файлах (меняется от 5 до 1)
extern CString csNodeName; //имя открытого для работы файла дерева
extern BOOL bHideShowTest; //скрыть/отобразить окно теста
extern BOOL bCycleCheck; // проверять/ не проверять наличие циклов в дереве
extern BOOL bAutoCheck; //диатест с самопроверкой
//цвета для текстовых сообщений
extern COLORREF G_WRITESIG;
extern COLORREF G_ALERT;
extern COLORREF G_INFORMATION;
extern COLORREF G_MESSAGE; 
extern void Sort(CStringArray* HN,UINT index); //сортировка массивов
extern CString csHead; // ЗАГОЛОВОК
