import requests
import json


def test_adding_order():
    print("====test_adding_order====")
    with open("adding_order_test_file.json", "r") as file:
        data = json.load(file)
    
    url = "http://localhost:8080"

    for order in data:
        requests.post(url + "/addOrder", json=order)

    response = requests.get(url + "/getTrees", json=order)

    try:
        json_body = response.json()
        print("Response JSON:", json_body)
    except json.JSONDecodeError:
        print("Response is not valid JSON.")

    response = requests.get(url + "/getHighestBuyAndLowestSell", json=order)

    try:
        json_body = response.json()
        print("Response JSON:", json_body)
    except json.JSONDecodeError:
        print("Response is not valid JSON.")


def test_cancelling_order():
    print("====test_cancelling_order====")
    with open("cancel_order_test_file.json", "r") as file:
        data = json.load(file)

    url = "http://localhost:8080"

    for order in data:
        requests.post(url + "/cancelOrder", json=order)

    response = requests.get(url + "/getTrees", json=order)

    try:
        json_body = response.json()
        print("Response JSON:", json_body)
    except json.JSONDecodeError:
        print("Response is not valid JSON.")

    response = requests.get(url + "/getHighestBuyAndLowestSell", json=order)

    try:
        json_body = response.json()
        print("Response JSON:", json_body)
    except json.JSONDecodeError:
        print("Response is not valid JSON.")

def test_executing_order():
    print("====test_executing_order====")
    with open("execute_order_test_file.json", "r") as file:
        data = json.load(file)

    url = "http://localhost:8080"

    for order in data:
        requests.post(url + "/executeOrder", json=order)

    response = requests.get(url + "/getTrees", json=order)

    try:
        json_body = response.json()
        print("Response JSON:", json_body)
    except json.JSONDecodeError:
        print("Response is not valid JSON.")

    response = requests.get(url + "/getHighestBuyAndLowestSell", json=order)

    try:
        json_body = response.json()
        print("Response JSON:", json_body)
    except json.JSONDecodeError:
        print("Response is not valid JSON.")

if __name__ == "__main__":
    test_adding_order()
    test_cancelling_order()
    test_executing_order()