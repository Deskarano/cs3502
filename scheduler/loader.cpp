// loader goes here copy from other branch. pulling from file to disk. parse file while has next line load to disk. make pcb (record first location on disk and the length)
// translate into binary translate hex into unsigned int then saving to disk

if(program.is_open())
{
    while(std::getline(program, line))
    {
        if(line[0] != '/')
        {
            auto value = (unsigned) std::stoul(line, nullptr, 16);
            cpu_test_ram::write_word(addr, value);
            addr += 4;
        }
    }
}
else
{
    std::cout << "unable to open file\n";
    return 1;
}
