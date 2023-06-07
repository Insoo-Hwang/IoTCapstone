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


## 시나리오

**소비자 입장**
  - 회원가입 후 자신의 취향 정보 및 성별 나이대를 입력.
  - 매장 이용시 QR코드를 입력.
  - 매장에 설치된 카메라가 입장한 소비자를 따라다니며 어느 구역에 위치해 있는지 확인.
  - 소비자가 미리 입력한 정보 및 구매 이력을 파악하여 해당 위치에 있는 추천 상품을 Arduino LCD를 통해 표시.

**관리자 입장**
  - 상품 위치 정보 및 상품에 대한 정보를 입력시 해당 위치의 Arduino LCD에 입력한 상품 정보 표시.
  - 위치 정보를 입력시 해당 위치에 어떤 상품이 있는지 조회.
  - 사용자가 QR코드 입력시 해당 사용자 uid를 AWS DB에 저장.


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

| 아두이노 LCD | 라즈베리파이 카메라 화면 | - |
|:-------------------------------------:|:-------------------------------------------------:|:-------------------------------------------------:|
|![KakaoTalk_20230607_135751463_02](https://github.com/Insoo-Hwang/IoTCapstone/assets/70841847/c2215ddc-e895-4d47-a3b3-e29116c96929)|![KakaoTalk_20230607_150914397](https://github.com/Insoo-Hwang/IoTCapstone/assets/70841847/adddc1b8-a0f7-4175-a603-88a3ae89cbe9)| - |


## 상품 추천 알고리즘
![알고리즘](https://github.com/Insoo-Hwang/IoTCapstone/assets/70841847/4cbbdb4f-9378-4f56-ad6d-c0c4a8597ed4)


## 기대 효과
  - 소비자 입장에서는 자신의 위치에 따라 상품을 추천받을 수 있고 관리자 입장에서는 상품의 정보를 직접 바꾸지 않고 Android APP을 통해 손쉽게 바꿀 수 있음.
