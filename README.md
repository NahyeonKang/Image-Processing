# Image-Processing
![image](https://user-images.githubusercontent.com/24906028/173172176-5e293ef4-2edb-4bb9-9019-e9fdae6c5812.png)

## 개발 목표
남녀 얼굴 특성을 활용하여 성별을 구분하기

![image](https://user-images.githubusercontent.com/24906028/173172230-900e3542-c63f-4ff8-80a8-f61578eb84a4.png)

## WorkFlow
얼굴 영상 수집 및 전처리  
→ 얼굴 및 눈 검출  
→ 검출된 눈 좌표로 얼굴 기울기 계산 및 보정  
수염 검출
→ 각 피처 마스크 생성 → 피처별 히스토그램 계산  
→ 히스토그램 유사도 계산 → 유사도 비교
눈썹 검출
캐니에지 검출 후 컨투어 선 그리기 → 선 개수 카운트   

## 개발 내용
![image](https://user-images.githubusercontent.com/24906028/173172257-56f44f7d-8f7e-400f-8350-97a9f8d50ff8.png)
여자는 수염이 없는 경우가 대부분 -> 볼과 입 주변의 히스토그램을 비교하여 수염유무를 판단해 1차적으로 남녀를 구분!
수염이 없는 남자와 여자 구분 -> 여자의 눈썹은 얇고 긴 경우가 많아 에지 검출 후 컨투어 선을 그려 선 개수 카운트 -> 개수가 적으면 여자

## 개발 과정
1. 얼굴 및 눈 검출  
콧구멍이 큰 사진일 경우 눈으로 3개 이상이 검출되어 2개만 검출될 때까지 사이즈 수정
![image](https://user-images.githubusercontent.com/24906028/173172346-764e46b2-33ef-4056-bd02-7e161a518984.png)
![image](https://user-images.githubusercontent.com/24906028/173172348-c6178fed-a1c2-4d7d-a631-6169d1838bbb.png)
2. 검출된 눈 좌표로 얼굴 기울기 계산 및 보정  
![image](https://user-images.githubusercontent.com/24906028/173172363-158373d9-4ef4-454b-9e98-897013402042.png)
3. 각 피처 마스크 생성  
![image](https://user-images.githubusercontent.com/24906028/173172375-4fbeab43-c58a-4005-8f03-e20d709f1b12.png)
![image](https://user-images.githubusercontent.com/24906028/173172393-6d2eaaf3-4d07-43a0-be4d-62d80bf89f74.png)
4. 수염 검출 - 피처별 히스토그램 계산 후 유사도 비교
컬러영상은 히스토그램이 조명이나 피부색의 영향이 커
명암도영상으로 변환 후 히스토그램 측정
![image](https://user-images.githubusercontent.com/24906028/173172418-0ab44fbc-44ca-40f1-906a-c5743b0a3a7d.png)
![image](https://user-images.githubusercontent.com/24906028/173172424-69073542-6cf1-4393-9810-6aef376b988a.png)
![image](https://user-images.githubusercontent.com/24906028/173172427-9975b045-b671-4064-8f34-71e10aa01a4d.png)
5. 눈썹 검출 - 캐니에지 검출 후 컨투어 선 그린 후 선 개수 카운트
![image](https://user-images.githubusercontent.com/24906028/173172512-440ed882-5a75-4265-a628-c1ad9182541e.png)
![image](https://user-images.githubusercontent.com/24906028/173172515-e22421d0-d2a0-4536-ac40-97c96a283b0f.png)
![image](https://user-images.githubusercontent.com/24906028/173172517-42c97b29-d7fc-4f99-b0bb-290f3f54879c.png)
6. 값을 점수화해 남녀 구분
![image](https://user-images.githubusercontent.com/24906028/173172536-90ed0fe5-9690-40b1-9ed6-5fa437d45e7f.png)
7. 결과 화면
![image](https://user-images.githubusercontent.com/24906028/173172546-0e38f991-8217-4a33-a9df-5965fa5f3af4.png)
![image](https://user-images.githubusercontent.com/24906028/173172551-a079b190-1230-4b64-a34e-dfa501167497.png)
![image](https://user-images.githubusercontent.com/24906028/173172555-77aaebf9-880a-4804-b568-05dca973acb4.png)
![image](https://user-images.githubusercontent.com/24906028/173172558-5b77cc62-dbaa-4d96-9e64-701c717e78a0.png)
![image](https://user-images.githubusercontent.com/24906028/173172561-e494d583-3341-45a2-a00c-91a8c78dbcae.png)
![image](https://user-images.githubusercontent.com/24906028/173172564-9f8d7b2a-e4bf-4fe0-a225-8728d7855a5e.png)
![image](https://user-images.githubusercontent.com/24906028/173172567-9477f89c-03ed-4504-be55-422f7c994b68.png)
![image](https://user-images.githubusercontent.com/24906028/173172571-b526b23d-c423-4f45-948a-f24806f8d875.png)
