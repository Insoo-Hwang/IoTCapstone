# IoTCapstone
## 프로젝트명
스마트 선반대

## 팀 구성
강민아(2071442), 오채영(2071357), 황인수(1771294)

## 개발 목적
최근 코로나 19시대와 인건비 상승으로 인하여 무인매장의 수요가 급격히 늘었다. 이러한 수요에 맞춰 무인매장에서 손쉽게 이용할 수 있는 스마트 선반대를 기획하게 되었다.

## 사용 기술과 구조

### 적용 기술
**개발 언어** Kotlin(Android App), C++(Arduino), Python(Rasberry PI, AWS Lambda)

**개발 항목** Android APP, Arduino, Rasberry PI, AWS Cloud

### 구조
![구조도](https://github.com/Insoo-Hwang/IoTCapstone/assets/70841847/1d289ea7-c7e1-45c2-b4fb-723aa48b2895)


## 기능과 자료화면

| 로그인&회원가입 | 사용자 QR코드 | 사용자 정보 입력 |
|:-------------------------------------:|:-------------------------------------------------:|:-----------------------------------------------:|
|![1](https://github.com/Insoo-Hwang/IoTCapstone/assets/70841847/6dc3c975-d394-4721-ba5a-4456c5fdaf10)|![3](https://github.com/Insoo-Hwang/IoTCapstone/assets/70841847/c06c27d3-16b2-4910-91f0-0814c8889a37)|![Screenshot_20230607_144845_IoT project real](https://github.com/Insoo-Hwang/IoTCapstone/assets/70841847/cdea99ec-33fa-4add-acba-b615761d9f8a)|

| 임시 구매 정보 입력 | 상품 위치 정보 입력&검색 | - |
|:-------------------------------------:|:-------------------------------------------------:|:-----------------------------------------------:|
|![Screenshot_20230607_145431_IoT project real](https://github.com/Insoo-Hwang/IoTCapstone/assets/70841847/30cf77f1-4722-41b4-85ce-9bdefcb998b9)|![Screenshot_20230607_145511_IoT project real](https://github.com/Insoo-Hwang/IoTCapstone/assets/70841847/fbabbf0d-1a65-43b5-bee4-62e148947939)| - |

| 사용자 정보 DB | 물건 정보 DB | - |
|:-------------------------------------:|:-------------------------------------------------:|:-----------------------------------------------:|
|![화면 캡처 2023-06-07 145956](https://github.com/Insoo-Hwang/IoTCapstone/assets/70841847/4a5888ca-9d12-4393-ab62-f264a654f06f)|![화면 캡처 2023-06-07 150029](https://github.com/Insoo-Hwang/IoTCapstone/assets/70841847/ffbe0467-6f40-45dc-94a5-885530278be1)| - |

| 공유 및 위치 정보 | 중간 지점 확인 | 일정 상세(수정) |
|:-------------------------------------:|:-------------------------------------------------:|:-------------------------------------------------:|
|![KakaoTalk_20230524_180608420_10](https://github.com/Insoo-Hwang/WooR2/assets/72377913/60538964-836d-446f-b951-04cc5cd43074)|![KakaoTalk_20230524_180608420_11](https://github.com/Insoo-Hwang/WooR2/assets/72377913/d221549f-4d73-4748-a8e8-6aa860905066)|![KakaoTalk_20230524_183245761](https://github.com/Insoo-Hwang/WooR2/assets/72377913/05f73a01-f1d9-42cd-88c7-c68b751658ca)|

## 기능 상세

**메인**
  - 자신의 일정 목록을 띄운다.
  - QR 버튼을 터치 시 공유용 QR코드를 띄운다.
  - 공유 버튼 터치 시 공유 코드를 복사할 수 있다.
  - 휴지통 버튼 터치 시 해당 일정을 삭제할 수 있다.

**일정 생성 & 일정 상세(수정)**
  1. 공개 체크박스를 통해 공개 여부를 정할 수 있다.
  2. 제목과 날짜를 정한다.
  3. 장소 검색 버튼을 통해 장소의 이름과 좌표값을 가져올 수 있다.
  4. 장소 추가 버튼을 통해 해당 장소를 일정에 추가한다.
  5. 저장하기 버튼을 눌러 일정을 저장한다.
  - 전체 경로 버튼을 통해 모든 장소의 경로를 볼 수 있다.
  - 화살표 버튼으로 장소의 순서를 변겅할 수 있다.
  - 경로 확인 버튼으로 카카오 맵으로 전환하여 이전 지점부터 해당 지점까지의 경로를 확인할 수 있다.
  - 휴지통 버튼 터치 시 해당 장소를 삭제할 수 있다.

**지도(장소 선택)**
  - 원하는 위치의 주소, 지명을 입력후 검색하면 해당 지역으로 이동할 수 있다.
  - 위 장소에 더하여 특정 검색어(카페, 편의점 등)를 함께 입력하면 해당 장소 주변의 검색 결과를 보여준다.
  - 원하는 장소의 마커를 터치하여 해당 장소를 일정에 추가할 수 있다.
  - 현위치 버튼을 터치 시 현재 위치로 카메라가 이동된다.

**일정 검색**
  - 일정의 이름을 검색하여 목록을 띄우고 원하는 일정을 자신의 일정으로 가져올 수 있다.

**추천 일정**
  - 특정 지역이나 테마의 일정 들이 목록에 나오고 해당 일정을 터치하여 확인 후 가져올 수 있다.

**공유 및 위치 정보** 
  - 본인의 UID를 확인하고 로그아웃 할 수 있다.
  - 전달받은 공유 코드를 이용하여 본인의 일정에 추가할 수 있다.
  - QR코드를 확인할 수 있는 카메라를 실행한다.
  - 원하는 장소를 카카오 맵에서 검색할 수 있다.
  - 두 지점 사이의 중간 지점을 확인할 수 있다.

## 기대 효과
  - 다양한 관계와 그룹 차원의 일정들을 생성하고 일정 별로 관리하거나 확인하는 데에 도움을 주어 일정을 정할 때의 시간 효율성을 높이고 새로운 관계를 만들거나 기존 관계에서의 만남을 용이하게 할 수 있다.
  - 개인별 맟춤 일정 추천 기능을 통해 기존의 틀에 벗어나 새로운 장소를 경험해 볼 수 있는 기회를 얻을 수 있다.
