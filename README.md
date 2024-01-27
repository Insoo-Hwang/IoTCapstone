# 스마트 진열대

## 팀 구성
* 강민아
  - 아두이노 파트
* 오채영
  - 라즈베리파이 파트
* 황인수
  - 안드로이드 및 AWS 파트

## 개발 동기
편의점 매대 앞에서 어떤 것을 선택해야할지 고민해본 경험은 다들 하나씩 있을 것이다. 이러한 고민과 최근 코로나 19, 인건비 상승으로 인해 증가한 무인매장의 수요에 맞춰 소비자에게는 상품을 추천하고 관리자는 쉽게 관리할 수 있는 스마트 진열대를 기획하게 되었다.
* [선택 관련 기사](http://www.psytimes.co.kr/news/view.php?idx=6627)
* [무인매장 관련 기사](https://www.mk.co.kr/news/economy/10865652)

## 사용 기술과 구조

### 적용 기술
**개발 언어** `Kotlin`(Android App), `C++`(Arduino), `Python`(Rasberry PI, AWS Lambda)

**개발 항목** Android APP, Arduino, Rasberry PI, AWS(Lambda, DynamoDB, Cognito, API Gateway, IoT Core)

### 구조
![구조도](https://github.com/Insoo-Hwang/IoTCapstone/assets/70841847/1d289ea7-c7e1-45c2-b4fb-723aa48b2895)


## 시나리오

**소비자 입장**
  - 회원가입 후 자신의 취향 정보 및 성별 나이대를 입력
  - 매장 이용시 QR코드를 입력
  - 매장에 설치된 카메라가 입장한 소비자를 따라다니며 어느 구역에 위치해 있는지 확인
  - 소비자가 미리 입력한 정보 및 구매 이력을 파악하여 해당 위치에 있는 추천 상품을 Arduino LCD를 통해 표시

**관리자 입장**
  - 상품 위치 정보 및 상품에 대한 정보를 입력시 해당 위치의 Arduino LCD에 입력한 상품 정보 표시
  - 위치 정보를 입력시 해당 위치에 어떤 상품이 있는지 조회
  - 사용자가 QR코드 입력시 해당 사용자 uid를 AWS DB에 저장


## 기능과 자료화면

| 로그인&회원가입 | 사용자 QR코드 | 사용자 정보 입력 |
|:-------------------------------------:|:-------------------------------------------------:|:-----------------------------------------------:|
|![1](https://github.com/Insoo-Hwang/IoTCapstone/assets/70841847/9de8eb6c-36b2-44b0-9931-1eec11a35b5f)|![2](https://github.com/Insoo-Hwang/IoTCapstone/assets/70841847/432063d0-10f1-462d-bac3-4938337b1e7b)|![Screenshot_20230607_144845_IoT project real](https://github.com/Insoo-Hwang/IoTCapstone/assets/70841847/cdea99ec-33fa-4add-acba-b615761d9f8a)|

| 임시 구매 정보 입력 | 상품 위치 정보 입력&검색 | - |
|:-------------------------------------:|:-------------------------------------------------:|:-----------------------------------------------:|
|![Screenshot_20230607_145431_IoT project real](https://github.com/Insoo-Hwang/IoTCapstone/assets/70841847/30cf77f1-4722-41b4-85ce-9bdefcb998b9)|![Screenshot_20230607_145511_IoT project real](https://github.com/Insoo-Hwang/IoTCapstone/assets/70841847/fbabbf0d-1a65-43b5-bee4-62e148947939)| - |

| 사용자 정보 DB | 물건 정보 DB | - |
|:-------------------------------------:|:-------------------------------------------------:|:-----------------------------------------------:|
|![화면 캡처 2023-06-07 145956](https://github.com/Insoo-Hwang/IoTCapstone/assets/70841847/4a5888ca-9d12-4393-ab62-f264a654f06f)|![화면 캡처 2023-06-07 150029](https://github.com/Insoo-Hwang/IoTCapstone/assets/70841847/ffbe0467-6f40-45dc-94a5-885530278be1)| - |

| 아두이노 LCD | 라즈베리파이 카메라 화면 | - |
|:-------------------------------------:|:-------------------------------------------------:|:-------------------------------------------------:|
|![1](https://github.com/Insoo-Hwang/IoTCapstone/assets/70841847/b07e840e-9e05-43bd-82cd-c8a490d669b2)|![KakaoTalk_20230607_150914397](https://github.com/Insoo-Hwang/IoTCapstone/assets/70841847/adddc1b8-a0f7-4175-a603-88a3ae89cbe9)| - |


## 상품 추천 알고리즘
![알고리즘](https://github.com/Insoo-Hwang/IoTCapstone/assets/70841847/4cbbdb4f-9378-4f56-ad6d-c0c4a8597ed4)
![image](https://github.com/Insoo-Hwang/IoTCapstone/assets/70841847/f92e2581-684f-4277-a8cd-e4ec41b3505d)
* 선호하는 상품에 더 큰 관심을 가지는 '디깅 소비'를 활용하여 상품과 소비자의 취향 정보(앱을 통해 입력한 부분 40% + 소비 패턴 60%)를 6개의 특징(매운, 짠, 단, 쓴, 신, 고소한)으로 나누어 수치화하고 점수를 부여하여 높은 점수에 있는 상품을 추천


## 기대 효과
  - 소비자 입장에서는 자신의 위치와 취향에 따라 상품을 추천받을 수 있어 고민하는 시간을 대폭 줄일 수 있음
  - 관리자 입장에서는 상품의 정보를 Android App을 통해 손쉽게 관리할 수 있음
