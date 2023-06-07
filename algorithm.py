import json
import boto3
from datetime import datetime

def lambda_handler(event, context):
    iot_client = boto3.client('iot-data')
    topic = 'topic/Rec'
    
    payload = {'message' : 'clear'}
    response = iot_client.publish(
        topic=topic,
        qos=1,
        payload=json.dumps(payload)
    )
    
    dynamodb = boto3.resource('dynamodb')
    s3_client = boto3.client('s3')
    
    s3_uri = 's3://iotsend/trackig_raspberrypi'
    
    response = s3_client.get_object(Bucket=s3_uri.split('/')[2], Key='/'.join(s3_uri.split('/')[3:]))
    file_content = response['Body'].read().decode('utf-8')
    user_loc = file_content[-1]
    user_code = file_content[:-1]
    
    print(user_loc)
    print(user_code)
    
    user = dynamodb.Table('User')
    product = dynamodb.Table('Product')
    
    response = user.get_item(Key={'Name': user_code})
    user_item = response['Item']
    User_Age = user_item.get('Age') if user_item else None
    User_Gen = user_item.get('Gender') if user_item else None
    A = int(user_item.get('A') if user_item else None)
    B = int(user_item.get('B') if user_item else None)
    C = int(user_item.get('C') if user_item else None)
    D = int(user_item.get('D') if user_item else None)
    E = int(user_item.get('E') if user_item else None)
    F = int(user_item.get('F') if user_item else None)
    
    if user_loc == 'L':
        response = product.get_item(Key={'Location': '1'})
        product_item1 = response['Item']
        response = product.get_item(Key={'Location': '2'})
        product_item2 = response['Item']
    elif user_loc == 'R':
        response = product.get_item(Key={'Location': '3'})
        product_item1 = response['Item']
        response = product.get_item(Key={'Location': '4'})
        product_item2 = response['Item']
    else:
        print("Failed")
        
    print(product_item1)
    print(product_item2)
    
    H1 = product_item1.get('Hot') if product_item1 else None
    H2 = product_item2.get('Hot') if product_item2 else None
    L1 = product_item1.get('Location') if product_item1 else None
    L2 = product_item2.get('Location') if product_item2 else None
    A1 = product_item1.get('A') if product_item1 else None
    B1 = product_item1.get('B') if product_item1 else None
    C1 = product_item1.get('C') if product_item1 else None
    D1 = product_item1.get('D') if product_item1 else None
    E1 = product_item1.get('E') if product_item1 else None
    F1 = product_item1.get('F') if product_item1 else None
    Age1 = product_item1.get('Age') if product_item1 else None
    Gen1 = product_item1.get('Gender') if product_item1 else None
    A2 = product_item2.get('A') if product_item2 else None
    B2 = product_item2.get('B') if product_item2 else None
    C2 = product_item2.get('C') if product_item2 else None
    D2 = product_item2.get('D') if product_item2 else None
    E2 = product_item2.get('E') if product_item2 else None
    F2 = product_item2.get('F') if product_item2 else None
    Age2 = product_item2.get('Age') if product_item2 else None
    Gen2 = product_item2.get('Gender') if product_item2 else None
    
    R1 = A*A1 + B*B1 + C*C1 + D*D1 + E*E1 + F*F1 - abs(User_Age-Age1)
    R2 = A*A2 + B*B2 + C*C2 + D*D2 + E*E2 + F*F2 - abs(User_Age-Age2)
    
    if User_Gen != Gen1:
        R1 = R1 - 20
    if User_Gen != Gen2:
        R2 = R2 -20
    
    if R1 > R2:
        if H1:
            payload = {'message' : L2}
            response = iot_client.publish(
                topic=topic,
                qos=1, 
                payload=json.dumps(payload)
            )
        else:
            payload = {'message' : L1}
            response = iot_client.publish(
                topic=topic,
                qos=1, 
                payload=json.dumps(payload)
            )
    else:
        if H2:
            payload = {'message' : L1}
            response = iot_client.publish(
                topic=topic,
                qos=1, 
                payload=json.dumps(payload)
            )
        else:
            payload = {'message' : L2}
            response = iot_client.publish(
                topic=topic,
                qos=1, 
                payload=json.dumps(payload)
            )

    month = datetime.now().month
    if month in [10, 11, 12, 1, 2]:
        if H1:
            payload = {'message' : L1}
            response = iot_client.publish(
                topic=topic,
                qos=1,
                payload=json.dumps(payload)
            )
        if H2:
            payload = {'message' : L2}
            response = iot_client.publish(
                topic=topic,
                qos=1,
                payload=json.dumps(payload)
            )  
    else:
        print("need Cold")

    return {
        'statusCode': 200,
        'body': json.dumps('Hello from Lambda!')
    }
