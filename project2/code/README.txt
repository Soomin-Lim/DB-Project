------설치 프로그램------
C++ 프로그램을 실행하기 전 MYSQL Server 8.0.29, MYSQL Workbench 8.0.29, MYSQL Connector/C++ 8.0.29, MYSQL Connector/ODBC 8.0.29, Visual Studio 2019을 설치해야 한다.

------MYSQL Connection 생성 및 DB 생성------
그 다음 MYSQL Workbench를 실행하여 새로운 MYSQL Connection을 생성한다.
Hostname은 localhost, Username는 root, Password는 mysql로 설정하여 새로운 Connection을 생성한다.
그 후 새로 생성한 MYSQL Connection에 연결한 다음 아래의 명령어를 입력하여 project 데이터베이스를 생성한다.
create database project;

데이터베이스가 생성되었는지는 다음 명령문을 통해 확인할 수 있다.
show databases;


------MYSQL Connection 생성 이후 주의 사항------
만약 MYSQL workbench가 safe update mode를 쓴다면 safe mode를 disable하기 위해 Edit -> Preferences -> SQL Editor, "Safe Updates" check box를 체크 해제시키여 한다. 그리고 MySQL server에 다시 재접속해야 한다.
위 과정을 수행해야지만 CRUD 파일로 넘긴 delete 명령어가 제대로 수행된다.


------Visual Studio 프로그램의 실제 구동 환경 명세------
window10 64bit, i5-8265U, Intel(R) UHD Graphics 620, visual studio 2019 – Debug, x64


------제출 파일 전체 구성도------
[DBproject2] ---- 20191637.png
                      |_ 20191637.erwin
                      |_ [project2]20191637.pdf
	        |_ 20191637.zip ---- Project2 폴더 ---- 20191637.cpp
                  		       |_ Project2.sln       |_ 20191637.txt
                  		       |_ README.txt	    |_ libmysql.dll
					    |_ Project2.vcxproj
					    |_ Project2.vcxproj.filters
					    |_ Project2.vcxproj.user

------프로그램 사용 전 주의사항----------
"mysql.h"를 포함하기 위해
추가 포함 디렉터리에 C:\Program Files\MySQL\MySQL Server 8.0\include;를 추가하므로 해당 위치에 include 폴더가 있어야한다.
또한 추가 라이브러리 디렉터리로 C:\Program Files\MySQL\MySQL Server 8.0\lib;를 추가하므로 해당위치에 lib 폴더가 있어야 한다.
해당 위치에 폴더가 없을 경우 프로그램이 실행되지 않는다.


------프로그램 사용 방법----------
위의 20191637.zip을 압축해제 시킨 다음, Project2.sln 솔루션 파일을 열고 Ctrl + F5 을 눌러 프로그램을 실행시킨다.

프로그램을 실행시키면 MYSQL DBMS와 연결을 생성한 다음 쿼리 타입을 선택할 수 있는 SELECT 메뉴가 콘솔에 출력된다.
쿼리 타입은 1부터 7까지 있으며 쿼리 타입을 선택하는 방법은 키보드로 해당 타입의 숫자를 입력하고 엔터를 치면 된다.
타입을 선택하면 해당 타입에 대한 쿼리 결과를 콘솔에 출력하며 서브 메뉴가 없는 경우 다시 SELECT 메뉴로 돌아간다.
타입 1, 2, 3, 4는 서브타입을 선택할 수 있는 서브 메뉴가 출력되며 이 때도 키보드로 해당 서브 타입의 숫자를 입력하고 엔터를 치면 해당 서브 타입에 대한 쿼리 결과가 콘솔에 출력되며 다시 SELECT 메뉴로 돌아간다.

만약 SELECT 메뉴나 서브 메뉴에서 쿼리 타입을 선택할 때 0을 선택한다면 프로그램은 그 즉시 종료된다.
