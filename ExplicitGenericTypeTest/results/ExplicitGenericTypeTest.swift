class TestClass {
  func testMethod() -> Void {
      let result: [String]? = [String]()
      let map: [String: Int]? = [
        "x": 5
      ]
      let keys: [String]? = Array(map!.keys)
      print(result)
      print(keys)
  }
}

TestClass().testMethod()