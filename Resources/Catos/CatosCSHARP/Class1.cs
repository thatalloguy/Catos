using catos;
using System.Diagnostics.Metrics;
using System.Reflection;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;

struct DummyComponent
{
    float data;
};

struct OtherComponent
{
    float data;
};

struct Cpp
{

    public int _name;

    public void printCpp(int age)
    {
    }

    


}
struct TransformComponent
{
    public float x, y, z;
}

public class CSharpTesting
{
    CSharpTesting()
    {
        Cpp testing = new Cpp();
        testing._name = 5;
        testing.printCpp(4);

        catos.Console con = new catos.Console();

        con.log("hello world from cpp");


        Entity entity = new Entity();

        System.Console.WriteLine("Has Component: " + entity.has_component<TransformComponent>());
        System.Console.WriteLine("Has Component: " + entity.has_component<DummyComponent>());
        System.Console.WriteLine("Transform X: " + entity.get_component<TransformComponent>().x);

    }

    public float MyPublicFloatVar = 5.0f;

    private string m_Name = "Hello";
    public string Name
    {
        get => m_Name;
        set
        {
            m_Name = value;
            MyPublicFloatVar += 5.0f;
        }
    }

    public void PrintFloatVar()
    {
/*        Console.WriteLine("Hello world from  C#!");
        Console.WriteLine("My name is: " + m_Name);
        Console.WriteLine("MyPublicFloatVar = " + MyPublicFloatVar);*/
    }

    private void IncrementFloatVar(float value)
    {
        MyPublicFloatVar += value;
    }

}

///Catos Lib (auto generated)
namespace catos
{
    struct Console
    {
        public void log(string msg)
        {
            LibNative.log_native(ref this, msg);
        }
    }


    public class Entity
    {

        public Entity()
        {
            handle = LibNative.entity_get_new_instance();
        }

        ~Entity()
        {
            LibNative.entity_destroy_instance(handle);
        }

        public bool has_component<T>()
        {
            String t = "struct " + typeof(T).Name;
            return LibNative.entity_has_component_native(handle, t);
        }

        public ref T get_component<T>() where T : unmanaged
        {
            String t = "struct " + typeof(T).Name;
            unsafe
            {
                return ref *(T*)LibNative.entity_get_component(handle, t);
            }
        }

        private IntPtr handle;

    }


    class LibNative
    {

        //BEGIN DEF For Console
        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        public static extern void log_native(ref Console instance, string msg);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        public static extern bool entity_has_component_native(IntPtr handle, string type);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        public static extern IntPtr entity_get_new_instance();

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        public static extern void entity_destroy_instance(IntPtr handle);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        public static unsafe extern void* entity_get_component(IntPtr handle, String name);


        //END DEF For Console

        /*       [MethodImplAttribute(MethodImplOptions.InternalCall)]
               public static extern Entity get_dummy_entity();

               [MethodImplAttribute(MethodImplOptions.InternalCall)]
               public static extern Entity get_dummy_entity();*/


    }
}///NAMESPACE CATOS 

