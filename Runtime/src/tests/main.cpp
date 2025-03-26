#pragma once
#define DOCTEST_CONFIG_IMPLEMENT
#include "../doctest/doctest/doctest.h"

#include <string> // NEW: For testing string properties/values
#include <memory> // NEW: For testing with smart pointers if needed
#include <stdexcept> // NEW: For potential exception testing

// Assuming these headers exist and provide the necessary functionality
#include "core/registry.h"
#include "core/application.h"
#include "stl/vector.h"
#include "stl/hashmap.h"
#include "core/logger.h" // NEW: Assuming a logger exists for potential integration

// --- Enhanced Test Structures ---

// Enhanced Foo with more features
struct Foo {
    int id = 0;
    float data = 2.0f;
    std::string name = "DefaultFoo";
    static int instance_count; // NEW: Static member

    // NEW: Constructor
    Foo(int i = 0, float d = 2.0f, std::string n = "DefaultFoo") : id(i), data(d), name(std::move(n)) {
        instance_count++;
        // CATOS_INFO("Foo({}) created", id); // Example Logger integration
    }

    // NEW: Destructor (for tracking lifetime, especially with vector/map)
    ~Foo() {
        instance_count--;
        // CATOS_INFO("Foo({}) destroyed", id);
    }

    // NEW: Copy Constructor
    Foo(const Foo& other) : id(other.id), data(other.data), name(other.name) {
        instance_count++;
        // CATOS_INFO("Foo({}) copy-constructed", id);
    }

    // NEW: Move Constructor
    Foo(Foo&& other) noexcept : id(other.id), data(other.data), name(std::move(other.name)) {
        instance_count++;
        other.id = -1; // Mark moved-from object
        // CATOS_INFO("Foo({}) move-constructed", id);
    }

    // NEW: Copy Assignment
    Foo& operator=(const Foo& other) {
        if (this != &other) {
            id = other.id;
            data = other.data;
            name = other.name;
            // CATOS_INFO("Foo({}) copy-assigned", id);
        }
        return *this;
    }

    // NEW: Move Assignment
    Foo& operator=(Foo&& other) noexcept {
        if (this != &other) {
            id = other.id;
            data = other.data;
            name = std::move(other.name);
            other.id = -1; // Mark moved-from object
            // CATOS_INFO("Foo({}) move-assigned", id);
        }
        return *this;
    }


    float get_data() const { // NEW: Made const
        return data;
    }

    // NEW: Method with parameters (assuming Registry supports this)
    void set_data(float new_data, const std::string& new_name) {
        data = new_data;
        name = new_name;
    }

    // NEW: Static method (assuming Registry supports this)
    static std::string get_type_name() {
        return "Foo";
    }

    // NEW: For vector/map testing comparison
    bool operator==(const Foo& other) const {
        return id == other.id && data == other.data && name == other.name;
    }
    bool operator!=(const Foo& other) const {
        return !(*this == other);
    }
};

int Foo::instance_count = 0; // Initialize static member

// Enhanced TransformComponent
struct TransformComponent {
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;

    // Corrected operator!=
    bool operator!=(const TransformComponent& b) const {
        return x != b.x || y != b.y || z != b.z;
    }

    // NEW: Added operator==
    bool operator==(const TransformComponent& b) const {
        return x == b.x && y == b.y && z == b.z;
    }

    // NEW: Method for registry testing
    void translate(float dx, float dy, float dz) {
        x += dx;
        y += dy;
        z += dz;
    }
};

// Renamed ComponentTest to PhysicsComponent for clarity
struct PhysicsComponent {
    float velocity_x = 0.0f;
    float velocity_y = 0.0f;
    float mass = 1.0f;

    // NEW: Method for registry testing
    float get_speed() const {
        return std::sqrt(velocity_x * velocity_x + velocity_y * velocity_y);
    }
};

// NEW: Another class for registry testing, possibly inheritance
struct Bar : Foo {
    bool is_special = false;

    Bar(int i = 0, float d = 5.0f, std::string n = "DefaultBar", bool s = true)
        : Foo(i, d, n), is_special(s) {}

    std::string get_bar_status() const {
        return name + (is_special ? " is special" : " is not special");
    }
};

// NEW: Simple services for Application testing
struct ServiceA {
    virtual ~ServiceA() = default; // Good practice for potential inheritance
    virtual std::string provide_service() { return "ServiceA Provided"; }
    int value = 10;
};

struct ServiceB {
    ServiceA* service_a_dependency = nullptr; // Example dependency
    std::string config_value = "Default B";

    ServiceB(ServiceA* dep = nullptr) : service_a_dependency(dep) {}

    std::string do_something_with_a() {
        if (service_a_dependency) {
            return "ServiceB using " + service_a_dependency->provide_service() + " with config " + config_value;
        }
        return "ServiceB (No ServiceA dependency) with config " + config_value;
    }
};

// NEW: Custom hash struct for testing hashmap with custom types
struct FooHash {
    std::size_t operator()(const Foo& f) const {
        // Simple hash combining id and name hash
        std::size_t h1 = std::hash<int>{}(f.id);
        std::size_t h2 = std::hash<std::string>{}(f.name);
        return h1 ^ (h2 << 1); // Combine hashes (simple example)
    }
};


namespace catos::tests {

    // --- Enhanced Registry Tests ---
    TEST_CASE("REGISTRY::Comprehensive Tests") {
        Registry registry;
        Foo foo_instance(1, 10.5f, "TestFoo");
        Bar bar_instance(2, 20.5f, "TestBar", true);

        // Register Foo
        auto& foo_class_reg = registry.register_class<Foo>("Foo")
            .property("id", &Foo::id, "Instance ID")
            .property("data", &Foo::data, "Floating point data")
            .property("name", &Foo::name, "Instance name")
            // .property("instance_count", &Foo::instance_count, "Static count") // Assuming static members need special handling (if supported)
            .method("get_data", &Foo::get_data, "Returns the data of Foo")
            // .method("set_data", &Foo::set_data, "Sets data and name") // Assuming methods with params need special handling (if supported)
            // .method("get_type_name", &Foo::get_type_name, "Static method example") // Assuming static methods need special handling (if supported)
            ;

        // Register Bar (potentially with base class info if supported)
        auto& bar_class_reg = registry.register_class<Bar>("Bar")
             // .base<Foo>() // Example syntax if inheritance is supported
            .property("id", &Bar::id, "Instance ID (from Foo)") // Re-register or inherit? Depends on Registry design
            .property("data", &Bar::data, "Floating point data (from Foo)")
            .property("name", &Bar::name, "Instance name (from Foo)")
            .property("is_special", &Bar::is_special, "Special flag for Bar")
            .method("get_data", &Bar::get_data, "Returns the data (from Foo)") // Re-register or inherit?
            .method("get_bar_status", &Bar::get_bar_status, "Gets Bar's status string")
            ;

        // Register TransformComponent
         registry.register_class<TransformComponent>("Transform")
            .property("x", &TransformComponent::x, "X coordinate")
            .property("y", &TransformComponent::y, "Y coordinate")
            .property("z", &TransformComponent::z, "Z coordinate")
            .method("translate", &TransformComponent::translate, "Moves the transform")
            ;

        // Register PhysicsComponent
        registry.register_class<PhysicsComponent>("Physics")
            .property("velocity_x", &PhysicsComponent::velocity_x, "X velocity")
            .property("velocity_y", &PhysicsComponent::velocity_y, "Y velocity")
            .property("mass", &PhysicsComponent::mass, "Object mass")
            .method("get_speed", &PhysicsComponent::get_speed, "Calculates magnitude of velocity")
            ;

        SUBCASE("Property Access and Validation") {
            Property* prop_data = foo_class_reg.get_property("data");
            Property* prop_name = foo_class_reg.get_property("name");
            Property* prop_non_existent = foo_class_reg.get_property("non_existent");

            REQUIRE(prop_data != nullptr);
            REQUIRE(prop_name != nullptr);
            CHECK(prop_non_existent == nullptr); // Check getting non-existent property

            // Assuming get_value returns void* which needs casting
            float* data_ptr = static_cast<float*>(prop_data->get_value(&foo_instance));
            std::string* name_ptr = static_cast<std::string*>(prop_name->get_value(&foo_instance));

            REQUIRE(data_ptr != nullptr);
            REQUIRE(name_ptr != nullptr);

            CHECK(*data_ptr == 10.5f);
            CHECK(*name_ptr == "TestFoo");

            // Modify through reflection (if setter exists or direct pointer modification works)
            *data_ptr = 11.0f;
            *name_ptr = "ModifiedFoo";
            CHECK(foo_instance.data == 11.0f);
            CHECK(foo_instance.name == "ModifiedFoo");
        }

        SUBCASE("Method Invocation and Validation") {
            Method* meth_get_data = foo_class_reg.get_method("get_data");
            Method* meth_non_existent = foo_class_reg.get_method("non_existent");

            REQUIRE(meth_get_data != nullptr);
            CHECK(meth_non_existent == nullptr); // Check getting non-existent method

            // Assuming invoke_function requires template argument for return type
            float result = meth_get_data->invoke_function<float>(&foo_instance);
            CHECK(result == foo_instance.data); // foo_instance.data might have been modified in previous subcase

             // Test method invocation on derived class instance via base registration (if applicable)
            Method* bar_meth_get_data = bar_class_reg.get_method("get_data");
            REQUIRE(bar_meth_get_data != nullptr);
            float bar_result = bar_meth_get_data->invoke_function<float>(&bar_instance);
            CHECK(bar_result == bar_instance.data);

            Method* bar_meth_status = bar_class_reg.get_method("get_bar_status");
            REQUIRE(bar_meth_status != nullptr);
            std::string status_result = bar_meth_status->invoke_function<std::string>(&bar_instance); // Assuming string return support
            CHECK(status_result == "TestBar is special");

            // TODO: Add tests for invoking methods with parameters once Registry support is confirmed/implemented
            // Example:
            // Method* meth_set_data = foo_class_reg.get_method("set_data");
            // if (meth_set_data) {
            //    meth_set_data->invoke_function<void>(&foo_instance, 15.0f, std::string("NewName"));
            //    CHECK(foo_instance.data == 15.0f);
            //    CHECK(foo_instance.name == "NewName");
            // }

             // TODO: Add tests for invoking static methods once Registry support is confirmed/implemented
        }

         SUBCASE("Handling Multiple Classes and Instances") {
             TransformComponent transform;
             transform.x = 1; transform.y = 2; transform.z = 3;

             auto* transform_reg = registry.get_class_registration("Transform");
             REQUIRE(transform_reg != nullptr);

             Property* prop_x = transform_reg->get_property("x");
             REQUIRE(prop_x != nullptr);
             float* x_ptr = static_cast<float*>(prop_x->get_value(&transform));
             CHECK(*x_ptr == 1.0f);

             // Method* meth_translate = transform_reg->get_method("translate");
             // REQUIRE(meth_translate != nullptr);
             // // Assuming invoke supports parameters:
             // meth_translate->invoke<void>(&transform, 0.5f, 0.0f, -1.0f);
             // CHECK(transform.x == 1.5f);
             // CHECK(transform.y == 2.0f);
             // CHECK(transform.z == 2.0f);
         }

         SUBCASE("Error Handling") {
             // Test getting non-existent class registration
             CHECK(registry.get_class_registration("NonExistentClass") == nullptr);

             // Test getting properties/methods from nullptr registration
             ClassRegistration* null_reg = nullptr;
             // These might crash if not handled internally, ideally they return nullptr or throw
             // CHECK(null_reg->get_property("data") == nullptr);
             // CHECK(null_reg->get_method("get_data") == nullptr);

             // Test invoking methods on null instance (should likely error or be disallowed)
             // Method* meth_get_data = foo_class_reg.get_method("get_data");
             // REQUIRE(meth_get_data != nullptr);
             // CHECK_THROWS_AS(meth_get_data->invoke_function<float>(nullptr), std::runtime_error); // Or appropriate error
         }

         // TODO: Add tests for unregistering classes if supported
         // SUBCASE("Unregistration") {
         //     CHECK(registry.unregister_class("Foo") == true);
         //     CHECK(registry.get_class_registration("Foo") == nullptr);
         //     CHECK(registry.unregister_class("NonExistent") == false);
         // }
    }


    // --- Enhanced Application Tests ---
    TEST_CASE("Application::Comprehensive Service Binding and Retrieval") {
        AppCreationInfo appinfo{};
        // Optionally configure logger or other settings in appinfo
        App app{&appinfo};

        REQUIRE(app.is_alive()); // Check if app initialization worked

        ServiceA service_a_instance;
        service_a_instance.value = 123;
        ServiceB service_b_instance(&service_a_instance); // Manual dependency injection for test instance
        service_b_instance.config_value = "Test Config";

        Foo unique_foo(99, 9.9f, "UniqueFoo");

        SUBCASE("Basic Binding and Retrieval") {
            app.bind<ServiceA>(&service_a_instance);
            app.bind<ServiceB>(&service_b_instance); // Bind instance with dependency already set

            ServiceA* retrieved_a = app.get<ServiceA>();
            ServiceB* retrieved_b = app.get<ServiceB>();

            REQUIRE(retrieved_a != nullptr);
            REQUIRE(retrieved_b != nullptr);

            CHECK(retrieved_a == &service_a_instance); // Check pointer equality
            CHECK(retrieved_b == &service_b_instance);
            CHECK(retrieved_a->value == 123);
            CHECK(retrieved_b->config_value == "Test Config");
            CHECK(retrieved_b->do_something_with_a() == "ServiceB using ServiceA Provided with config Test Config");
        }

        SUBCASE("Retrieval of Unbound Service") {
            // Assuming get returns nullptr if not bound
             Foo* retrieved_foo = app.get<Foo>();
             CHECK(retrieved_foo == nullptr);

            // Or, if it throws:
            // CHECK_THROWS_AS(app.get<Foo>(), std::runtime_error); // Or appropriate exception type
        }

        SUBCASE("Binding Multiple Distinct Types") {
             app.bind<ServiceA>(&service_a_instance);
             app.bind<Foo>(&unique_foo);

             ServiceA* retrieved_a = app.get<ServiceA>();
             Foo* retrieved_foo = app.get<Foo>();

             REQUIRE(retrieved_a != nullptr);
             REQUIRE(retrieved_foo != nullptr);
             CHECK(retrieved_a == &service_a_instance);
             CHECK(retrieved_foo == &unique_foo);
             CHECK(retrieved_foo->name == "UniqueFoo");
        }

        SUBCASE("Rebinding Service") {
            app.bind<ServiceA>(&service_a_instance);
            ServiceA* first_retrieval = app.get<ServiceA>();
            CHECK(first_retrieval == &service_a_instance);

            ServiceA another_service_a;
            another_service_a.value = 999;
            app.bind<ServiceA>(&another_service_a); // Rebind

            ServiceA* second_retrieval = app.get<ServiceA>();
            REQUIRE(second_retrieval != nullptr);
            CHECK(second_retrieval == &another_service_a); // Should now point to the new instance
            CHECK(second_retrieval->value == 999);
            CHECK(first_retrieval != second_retrieval);
        }

        // TODO: Add tests for unbinding if supported
        // SUBCASE("Unbinding Service") {
        //     app.bind<ServiceA>(&service_a_instance);
        //     REQUIRE(app.get<ServiceA>() != nullptr);
        //     CHECK(app.unbind<ServiceA>() == true); // Assuming unbind returns success/failure
        //     CHECK(app.get<ServiceA>() == nullptr); // Should be null after unbinding
        //     CHECK(app.unbind<ServiceA>() == false); // Cannot unbind already unbound service
        // }

        // TODO: Add tests for Application-managed instances / Dependency Injection if supported
        // SUBCASE("Application Managed Instances / DI") {
        //     // Assuming App can create instances and manage lifetime
        //     // Example syntax:
        //     app.register_and_create<ServiceA>();
        //     app.register_and_create<ServiceB>([](App& current_app){ // Factory lambda for DI
        //         return new ServiceB(current_app.get<ServiceA>());
        //     });
        //
        //     ServiceB* resolved_b = app.get<ServiceB>();
        //     REQUIRE(resolved_b != nullptr);
        //     REQUIRE(resolved_b->service_a_dependency != nullptr);
        //     CHECK(resolved_b->do_something_with_a() == "ServiceB using ServiceA Provided with config Default B");
        //
        //     // Need to check if 'app' correctly destroys these instances upon its own destruction
        // }
    }


    // --- Enhanced catos::vector Tests ---
    TEST_CASE("STL::vector Comprehensive Tests") {

        SUBCASE("Default Construction and Empty State") {
            catos::vector<int> vec_int;
            CHECK(vec_int.size() == 0);
            CHECK(vec_int.empty());
            CHECK(vec_int.capacity() == 0); // Or some small default capacity

            catos::vector<Foo> vec_foo;
            CHECK(vec_foo.size() == 0);
            CHECK(vec_foo.empty());
        }

        SUBCASE("push_back, size, capacity, and element access") {
            catos::vector<int> vec;
            CHECK(vec.capacity() == 0); // Assuming starts at 0

            vec.push_back(10);
            CHECK(vec.size() == 1);
            CHECK_FALSE(vec.empty());
            CHECK(vec[0] == 10);
            CHECK(vec.capacity() >= 1); // Capacity should grow

            vec.push_back(20);
            vec.push_back(30);
            CHECK(vec.size() == 3);
            CHECK(vec[1] == 20);
            CHECK(vec[2] == 30);

            size_t capacity_after_3 = vec.capacity();
            CHECK(capacity_after_3 >= 3);

            // Add more elements to potentially trigger reallocation
            for (int i = 4; i <= 10; ++i) {
                vec.push_back(i * 10);
            }
            CHECK(vec.size() == 10);
            CHECK(vec[9] == 100);
            CHECK(vec.capacity() >= capacity_after_3); // Might have reallocated
            CHECK(vec.capacity() >= 10);
        }

        SUBCASE("reserve") {
            catos::vector<std::string> vec;
            vec.reserve(10);
            CHECK(vec.size() == 0); // Reserve doesn't change size
            CHECK(vec.capacity() >= 10);

            size_t capacity_before = vec.capacity();
            vec.push_back("hello");
            vec.push_back("world");
            CHECK(vec.capacity() == capacity_before); // Should not reallocate yet

            vec.reserve(5); // Reserve less than current capacity should ideally do nothing
            CHECK(vec.capacity() == capacity_before);
            CHECK(vec.size() == 2);

            vec.reserve(capacity_before + 5); // Reserve more
            CHECK(vec.capacity() >= capacity_before + 5);
            CHECK(vec.size() == 2); // Size still unchanged
            CHECK(vec[0] == "hello");
        }

        SUBCASE("Iteration") {
            catos::vector<int> vec;
            vec.push_back(1);
            vec.push_back(2);
            vec.push_back(3);

            // Range-based for loop (const)
            int expected = 1;
            for (const int& val : vec) {
                CHECK(val == expected++);
            }
            CHECK(expected == 4); // Make sure loop executed correct number of times

            // Iterator loop (mutable)
            expected = 1;
            for (auto it = vec.begin(); it != vec.end(); ++it) {
                CHECK(*it == expected++);
                *it += 10; // Modify elements
            }
            CHECK(vec[0] == 11);
            CHECK(vec[1] == 12);
            CHECK(vec[2] == 13);

            // Const iterator loop
            expected = 11;
             const catos::vector<int>& const_vec = vec;
            for (auto it = const_vec.begin(); it != const_vec.end(); ++it) {
                 CHECK(*it == expected++);
            }
        }

        SUBCASE("clear") {
            catos::vector<int> vec;
            vec.push_back(1);
            vec.push_back(2);
            vec.reserve(10);
            size_t capacity_before = vec.capacity();

            vec.clear();
            CHECK(vec.size() == 0);
            CHECK(vec.empty());
            CHECK(vec.capacity() == capacity_before); // Clear usually doesn't change capacity
        }

        // --- Tests for Non-POD Type (Foo) ---
        SUBCASE("Vector with Non-POD Type (Foo)") {
             Foo::instance_count = 0; // Reset count for this subcase
             { // Scope for vector lifetime
                 catos::vector<Foo> vec_foo;
                 CHECK(Foo::instance_count == 0);

                 vec_foo.push_back(Foo(1, 1.0f, "A")); // Rvalue push_back (Move expected if implemented)
                 CHECK(vec_foo.size() == 1);
                 CHECK(vec_foo[0].id == 1);
                 CHECK(Foo::instance_count >= 1); // 1 if moved, 2 if copied

                 Foo f2(2, 2.0f, "B");
                 vec_foo.push_back(f2); // Lvalue push_back (Copy expected)
                 CHECK(vec_foo.size() == 2);
                 CHECK(vec_foo[1].id == 2);
                 CHECK(Foo::instance_count >= 2); // Should have original f2 + copy/move in vector

                 Foo f3(3, 3.0f, "C");
                 vec_foo.push_back(std::move(f3)); // Explicit move
                 CHECK(vec_foo.size() == 3);
                 CHECK(vec_foo[2].id == 3);
                 CHECK(f3.id == -1); // Check if moved-from object is marked
                 CHECK(Foo::instance_count >= 3);

                 // Test potential reallocation with non-POD
                 size_t initial_instances = Foo::instance_count;
                 vec_foo.reserve(vec_foo.capacity() * 2 + 1); // Force reallocation
                 CHECK(Foo::instance_count == initial_instances); // If move semantics work correctly during realloc
                 CHECK(vec_foo.size() == 3);
                 CHECK(vec_foo[0].id == 1);
                 CHECK(vec_foo[1].id == 2);
                 CHECK(vec_foo[2].id == 3);

                 // Check clear calls destructors
                 vec_foo.clear();
                 CHECK(vec_foo.size() == 0);
                 CHECK(Foo::instance_count == 1); // Only f2 should remain (f3 was moved from)
             } // vec_foo goes out of scope
             // Any remaining objects inside vec_foo should have been destroyed by clear
              CHECK(Foo::instance_count == 1); // f2 still exists
              Foo::instance_count = 0; // Clean up for next tests
        }

         // TODO: Add tests for resize() if implemented
         // TODO: Add tests for insert()/erase() if implemented
         // TODO: Add tests for copy/move construction/assignment of the vector itself
    }


    // --- Enhanced catos::hashmap Tests ---
    TEST_CASE("STL::hashmap Comprehensive Tests") {

        SUBCASE("Default Construction and Empty State") {
            catos::hashmap<int, std::string> map_is;
            CHECK(map_is.size() == 0);
            CHECK(map_is.empty());

            catos::hashmap<std::string, Foo> map_sf;
            CHECK(map_sf.size() == 0);
            CHECK(map_sf.empty());
        }

        SUBCASE("put, get, size, and basic operations") {
            catos::hashmap<int, int> map;
            map.put(1, 10);
            map.put(2, 20);
            CHECK(map.size() == 2);
            CHECK_FALSE(map.empty());

            CHECK(map.get(1) == 10);
            CHECK(map.get(2) == 20);

            // Test updating existing key
            map.put(1, 100);
            CHECK(map.size() == 2); // Size should not change
            CHECK(map.get(1) == 100); // Value should be updated
        }

        SUBCASE("get non-existent key") {
            catos::hashmap<int, int> map;
            map.put(1, 10);

            // Behavior depends on implementation:
            // Option 1: Throws exception
            // CHECK_THROWS_AS(map.get(99), std::out_of_range); // Or appropriate exception

            // Option 2: Returns default value (e.g., 0 for int) - Less safe generally
            // CHECK(map.get(99) == 0);
            // CHECK(map.size() == 2); // Careful: Default-value return might insert the key! Check size.

            // Option 3: Returns pointer or optional-like object
            // auto* val_ptr = map.try_get(99); // Assuming a try_get method
            // CHECK(val_ptr == nullptr);
            // REQUIRE(map.try_get(1) != nullptr);
            // CHECK(*map.try_get(1) == 10);

            // For the original test's check: map.get(40) == 100 with map.put(i, i + 60)
            // This assumes `get` behaves like Option 2 and default constructs, or throws.
            // The original test case `CHECK(map.get(40) == 100)` implies `get(40)` should return the value associated with key 40.
            // Since `put(40, 40+60)` was called, `get(40)` should indeed return 100. Let's refine that test.
             catos::hashmap<int, int> map_large;
             for (int i=0; i<100; i++) {
                 map_large.put(i, i + 60);
             }
             CHECK(map_large.get(40) == 100); // Correct retrieval
             // Add check for non-existent key based on expected behavior (e.g., throws or returns indicator)
             // CHECK_THROWS(map_large.get(200)); // Example if it throws
        }

        SUBCASE("contains (or find)") {
            catos::hashmap<int, std::string> map;
            map.put(5, "five");
            map.put(10, "ten");

            // Assuming a 'contains' method exists
            // CHECK(map.contains(5));
            // CHECK(map.contains(10));
            // CHECK_FALSE(map.contains(99));

            // Or if it uses find returning an iterator/pointer
            // CHECK(map.find(5) != map.end()); // Assuming STL-like iterators
            // CHECK(map.find(99) == map.end());
        }

         SUBCASE("remove (or erase)") {
             catos::hashmap<int, std::string> map;
             map.put(1, "a");
             map.put(2, "b");
             map.put(3, "c");
             REQUIRE(map.size() == 3);

             // Assuming remove/erase returns bool or number of elements removed
             bool removed_2 = map.remove(2); // Or map.erase(2)
             CHECK(removed_2);
             CHECK(map.size() == 2);
             // CHECK_FALSE(map.contains(2)); // Check key is gone

             bool removed_99 = map.remove(99); // Try removing non-existent
             CHECK_FALSE(removed_99);
             CHECK(map.size() == 2);

             CHECK(map.get(1) == "a"); // Check other elements remain
             CHECK(map.get(3) == "c");

             map.remove(1);
             map.remove(3);
             CHECK(map.size() == 0);
             CHECK(map.empty());
         }

         SUBCASE("clear") {
             catos::hashmap<int, int> map;
             map.put(10, 100);
             map.put(20, 200);
             REQUIRE(map.size() == 2);
             map.clear();
             CHECK(map.size() == 0);
             CHECK(map.empty());
             // Check if get/contains fails after clear
             // CHECK_THROWS(map.get(10));
             // CHECK_FALSE(map.contains(10));
         }

         SUBCASE("Rehashing / Load Factor") {
             catos::hashmap<int, int> map;
             // Assuming default load factor triggers rehashing
             size_t initial_capacity = map.capacity(); // Assuming capacity method exists
             for(int i = 0; i < 100; ++i) {
                 map.put(i, i*2);
             }
             CHECK(map.size() == 100);
             size_t final_capacity = map.capacity();
             // Rehashing should have occurred if initial capacity was small
             CHECK(final_capacity > initial_capacity); // Or CHECK(final_capacity > 100 / MAX_LOAD_FACTOR)
             // Verify data integrity after rehashing
             CHECK(map.get(50) == 100);
             CHECK(map.get(99) == 198);
         }


        // --- Tests for Non-POD Type (Foo) ---
        SUBCASE("Hashmap with Non-POD Type (Foo Key/Value)") {
             Foo::instance_count = 0; // Reset count
             {
                 // Using Foo as value
                 catos::hashmap<std::string, Foo> map_sf;
                 map_sf.put("A", Foo(1, 1.0f, "AVal")); // Rvalue put (move expected?)
                 CHECK(map_sf.size() == 1);
                 CHECK(Foo::instance_count >= 1); // 1 if moved, 2 if copied

                 Foo f_val(2, 2.0f, "BVal");
                 map_sf.put("B", f_val); // Lvalue put (copy expected)
                 CHECK(map_sf.size() == 2);
                 CHECK(Foo::instance_count >= 2);

                 map_sf.put("C", std::move(f_val)); // Explicit move value
                 CHECK(map_sf.size() == 3);
                 CHECK(f_val.id == -1); // Moved-from value marked
                 CHECK(Foo::instance_count >= 3);

                 // Check retrieval
                 Foo retrieved_a = map_sf.get("A"); // Assuming get returns by value (copy)
                 CHECK(retrieved_a.id == 1);
                 // Or if get returns ref/ptr: Foo& retrieved_a = map_sf.get("A");

                 // Check destructors called on map clear/destruction
                 size_t count_before_clear = Foo::instance_count;
                 map_sf.clear();
                 CHECK(map_sf.size() == 0);
                 // Expect 3 Foo objects in map to be destroyed
                 CHECK(Foo::instance_count == count_before_clear - 3);

                 // Using Foo as key (requires hash and equality)
                 catos::hashmap<Foo, int, FooHash> map_fi; // Using custom hasher
                 Foo f_key1(10, 1.0f, "Key1");
                 Foo f_key2(20, 2.0f, "Key2");

                 map_fi.put(f_key1, 100); // Lvalue put key (copy expected)
                 CHECK(map_fi.size() == 1);
                 CHECK(Foo::instance_count >= 1); // Original key + copy in map

                 map_fi.put(Foo(30, 3.0f, "Key3"), 300); // Rvalue put key (move expected?)
                 CHECK(map_fi.size() == 2);
                 CHECK(Foo::instance_count >= 2);

                 // Check retrieval with potentially different but equal key object
                 Foo f_key1_lookup(10, 1.0f, "Key1"); // Equal to f_key1
                 CHECK(map_fi.get(f_key1_lookup) == 100);

             } // Maps go out of scope
             // All Foo instances created within the scope should be destroyed
             CHECK(Foo::instance_count == 0);
        }

         // TODO: Add tests for iteration (key-value pairs) if supported
         // TODO: Add tests for copy/move construction/assignment of the hashmap itself
    }

} // namespace catos::tests


int main(int argc, char** argv) {
    // Initialize logger here if necessary
    // catos::Log::Init();
    // CATOS_INFO("Starting Tests...");

    doctest::Context context;
    context.applyCommandLine(argc, argv);
    context.setOption("no-breaks", true); // Continue after failed asserts in a test case
    context.setOption("order-by", "name"); // Optional: run tests alphabetically

    int res = context.run(); // Run tests

    if (context.shouldExit()) // important - query flags (and --exit) rely on this
        return res;

    // Optional: Add a pause or message if running from console
    // std::cout << "Tests finished. Press Enter to exit." << std::endl;
    // std::cin.get();

    return res;
}
