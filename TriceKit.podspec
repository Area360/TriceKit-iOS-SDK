Pod::Spec.new do |s|

  s.name                   = "TriceKit"
  s.version                = "0.3"
  s.summary                = "The TriceKit iOS SDK does things. Better summary coming soon."

  s.description            = <<-DESC
                   Todo:
                   A longer description of TriceKit in Markdown format.

                   * Think: Why did you write this? What is the focus? What does it do?
                   * CocoaPods will be using this to generate tags, and improve search results.
                   * Try to keep it short, snappy and to the point.
                   * Finally, don't worry about the indent, CocoaPods strips it! sgs
                   DESC

  s.homepage               = "http://tricekit.com/"
  s.license                = { :type => 'none', :text => "Copyright 2015 STQRY" }
  s.author                 = { "Jake" => "jake.bellamy@stqry.com" }
  s.platform               = :ios, "7.0"
  s.source                 = { :git => "https://github.com/stqry/TriceKit.git", :tag => s.version }
  s.requires_arc           = true
  s.xcconfig               = { 'OTHER_LDFLAGS' => '-lObjC -lc++' }
  s.source_files           = 'include/TriceKit.h'

  s.subspec 'Core' do |ss|
    ss.source_files = "include/TriceKitShared/*.h"
    ss.vendored_libraries  = 'libTriceKitShared.a'

    ss.dependency 'AFNetworking/NSURLSession', '~> 2.5'
    ss.dependency 'Mantle', '~> 1.5'
  end

  s.subspec 'ZTA' do |ss|
    ss.source_files = "include/TriceKitZTA/*.h"
    ss.vendored_libraries  = 'libTriceKitZTA.a'

    ss.dependency 'TriceKit/Core'
  end

end
